#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
#include <pwd.h>

#define BUF_SIZE 1
#define BRIGHTBLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"

sig_atomic_t interrupted = false;


enum ERR {NIL, ERROR, DONE, OS_ERR};
struct rtn {
	enum ERR err;
	void* ptr;
};
typedef struct rtn rtn_t;
rtn_t new_rtn() {
	rtn_t rtn;
	rtn.err = NIL;
	rtn.ptr = NULL;
	return rtn;
}

/*
 * Returns an input of arbitrary size
 */
char* get_line() {
	char b[BUF_SIZE];
	size_t length = 0;
	char* line = malloc(length+1);
	*line = '\0';
	for (;;) {
		size_t n = read(STDIN_FILENO, b, BUF_SIZE);
		if (n == -1) {
			if (interrupted == true) {
				printf("\n");
				break;
				interrupted = false;
			}
			fprintf(stderr, "Error: read() failed. %s.\n", strerror(errno));
			break;
		}
		if (n == 0) {
			break;
		}
		size_t prev = length;
		length += n;
		line = realloc(line, length+1);
		for (int i = 0; i < n; i++) {
			if (b[i] == '\n') {
				*(line+prev+i) = '\0';
				return line;
			}
			*(line+prev+i) = b[i];
		}
	}
	*(line+length) = '\0';
	return line;
}

struct cmd {
	size_t argc;
	char** argv;
};


/*
Needs error checking on the memory allocation
*/
rtn_t parse_line(const char* line, struct cmd* cmd) {
	rtn_t rtn = new_rtn();
	cmd->argc = 0;
	cmd->argv = malloc(cmd->argc*sizeof(char*));

	bool in_word = false;
	size_t cur_size = 0;
	for (; *line; line++) {
		if (*line == ' ' || *line == '\t') {
			if (in_word == true) {
				cmd->argv[cmd->argc-1] = realloc(cmd->argv[cmd->argc-1], ++cur_size*sizeof(char));
				cmd->argv[cmd->argc-1][cur_size-1] = '\0';
			}
			cur_size = 0;
			in_word = false;
			continue;
		}
		if (in_word == false) {
			in_word = true;
			cmd->argv = realloc(cmd->argv, ++cmd->argc*sizeof(char*));
			cmd->argv[cmd->argc-1] = malloc(cur_size*sizeof(char));
		}
		cmd->argv[cmd->argc-1] = realloc(cmd->argv[cmd->argc-1], ++cur_size*sizeof(char));
		cmd->argv[cmd->argc-1][cur_size-1] = *line;
	}
	if (in_word == true) {
		cmd->argv[cmd->argc-1] = realloc(cmd->argv[cmd->argc-1], ++cur_size*sizeof(char));
		cmd->argv[cmd->argc-1][cur_size-1] = '\0';
	}
	cmd->argv = realloc(cmd->argv, (cmd->argc + 1)*sizeof(char*));
	cmd->argv[cmd->argc] = NULL;
	return rtn;
}

rtn_t getpwuid_rtn(uid_t uid) {
	rtn_t rtn = new_rtn();
	struct passwd* pwuid;
	errno = 0;
	pwuid = getpwuid(uid);
	if (errno != 0) {
		rtn.err = OS_ERR;
		fprintf(stderr, "Error: getpwuid() failed. %s.\n", strerror(errno));
	} else if (pwuid == NULL) {
		rtn.err = ERROR;
	}
	rtn.ptr = pwuid;
	return rtn;
}

rtn_t chdir_rtn(const char* dir_name) {
	rtn_t rtn = new_rtn();
	if (chdir(dir_name) != 0) {
		rtn.err = OS_ERR;
		fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", dir_name, strerror(errno));
	}
	return rtn;
}

rtn_t get_home_dir() {
	rtn_t rtn = new_rtn();
	rtn = getpwuid_rtn(getuid()); // getuid() is always successful
	if (rtn.err != NIL) {
		return rtn;
	}
	rtn.ptr = ((struct passwd*)rtn.ptr)->pw_dir;
	return rtn;
}

rtn_t cd(struct cmd cmd) {
	rtn_t rtn = new_rtn();
	char* to_dir;
	if (cmd.argc == 1 || (cmd.argc == 2 && strcmp(cmd.argv[1], "~") == 0)) {
		rtn = get_home_dir();
		if (rtn.err != NIL) {
			return rtn;
		}
		to_dir = rtn.ptr;
	} else if (cmd.argc == 2) {
		to_dir = cmd.argv[1];
	}
	rtn = chdir_rtn(to_dir);
	return rtn;
}

rtn_t exit_built_in(struct cmd cmd) {
	rtn_t rtn = new_rtn();
	rtn.err = DONE;
	return rtn;
}

typedef rtn_t (*shell_built_in)(struct cmd);

rtn_t get_shell_built_in(struct cmd cmd) {
	rtn_t rtn = new_rtn();
	if (cmd.argc < 1)
		return rtn;

	if (strcmp(cmd.argv[0], "cd") == 0) {
		rtn.ptr = cd;
	} else if(strcmp(cmd.argv[0], "exit") == 0) {
		rtn.ptr = exit_built_in;
	}
	return rtn;
}


rtn_t execv_rtn(const char* pathname, char* const argv[], char* env[]) {
	rtn_t rtn = new_rtn();
	if (execvpe(pathname, argv, env) != 0) {
		rtn.err = DONE;
		fprintf(stderr, "Error: execv() failed. %s.\n", strerror(errno));
	}
	return rtn;
}

rtn_t shell_external(struct cmd cmd, char* env[]) {
	rtn_t rtn = new_rtn();
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error: fork() failed. %s\n", strerror(errno));
		rtn.err = OS_ERR;
		return rtn;
	}
	if (pid == 0) {
		if (cmd.argc < 1) {
			rtn.err = DONE;
			return rtn;
		}
		rtn = execv_rtn(cmd.argv[0], cmd.argv, env);
		return rtn;
	}
	int wstatus;
	while(waitpid(pid, &wstatus, WNOHANG) == 0);
	if (WIFSIGNALED(wstatus)) {
		printf("\n");
	}
	return rtn;
}

void catch_interupt(int sig) {
	interrupted = true;
}

int main(int argc, char* argv[], char* env[]) {
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = catch_interupt;

	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	rtn_t rtn = new_rtn();
	for (;rtn.err != DONE;) {
		// Dynamic memory
		char* line = NULL;
		char* wd = NULL;
		struct cmd cmd;
		cmd.argc = 0;
		cmd.argv = NULL;
		
		// Print prompt
		wd = malloc(PATH_MAX*sizeof(char));
		getcwd(wd, PATH_MAX);
		printf("[%s%s%s]$ ", BRIGHTBLUE, wd, DEFAULT);
		fflush(stdout);

		// Read and parse user input
		if ((line = get_line()) == NULL) {
			goto CLEANUP;
		}
		rtn = parse_line(line, &cmd);
		if (rtn.err != NIL) {
			goto CLEANUP;
		}


		if (cmd.argc == 0) {
			goto CLEANUP;
		}

		// Execute command
		rtn = get_shell_built_in(cmd);
		if (rtn.err != NIL) {
			goto CLEANUP;
		}
		if (rtn.ptr != NULL) {
			rtn = ((shell_built_in)rtn.ptr)(cmd);
			if (rtn.err != NIL) {
				goto CLEANUP;
			}
		} else {
			rtn = shell_external(cmd, env);			
		}

		// Cleanup
		CLEANUP:
		if (line != NULL)
			free(line);
		for (int i = 0; i < cmd.argc; i++) {
			if (cmd.argv[i] != NULL) {
				free(cmd.argv[i]);
			}
		}
		if (cmd.argv != NULL) {
			free(cmd.argv);
		}
		if (wd != NULL)
			free(wd);
	}
	return EXIT_SUCCESS;
}
