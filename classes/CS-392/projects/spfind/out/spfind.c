/*******************************************************************************
 * Name        : spfind.c
 * Author      : Ben Lirio
 * Date        : 3/31/2021
 * Description : spfind.c
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUF_SIZE 1029
#define NUM_CHANS 2

// pipe overhead
// opening and closing them
enum CHAN_MODE {READ, WRITE, UNUSED=-1};
struct chan {
	int pipe[2];
	enum CHAN_MODE mode;
};

struct chan new_chan() {
	struct chan chan;
	chan.mode = UNUSED;
	if (pipe(chan.pipe) == -1) {
		fprintf(stderr, "Error: pipe failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return chan;
}

void set_chan(struct chan *chan, enum CHAN_MODE mode) {
	chan->mode = mode;
	if (dup2(chan->pipe[mode], mode) == -1) {
		fprintf(stderr, "Error: dup3 failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (close(chan->pipe[mode == READ ? WRITE : READ]) == -1) {
		fprintf(stderr, "Error: close failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void close_chan(struct chan *chan) {
	if (chan->mode != UNUSED) {
		if (close(chan->pipe[chan->mode]) == -1) {
			fprintf(stderr, "Error: close failed. %s.\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else {
		if (close(chan->pipe[READ]) == -1) {
			fprintf(stderr, "Error: close failed. %s.\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (close(chan->pipe[WRITE]) == -1) {
			fprintf(stderr, "Error: close failed. %s.\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}

enum CHAN_NAMES {PFIND_TO_SORT, SORT_TO_PARENT};

int pfind_run(char *argv[]) {
	if (execv("pfind", argv) == UNUSED) {
		fprintf(stderr, "Error: pfind failed.\n");
	}
	return EXIT_FAILURE;
}
int sort_run(char *argv[]) {
	if (execl("/usr/bin/sort", "sort", NULL) == -1) {
		fprintf(stderr, "Error: sort failed.\n");
	}
	return EXIT_FAILURE;
}

struct proc {
	int (*run)(char **argv);
	struct chan chans[NUM_CHANS];
	int read_chan;
	int write_chan;
	char **argv;
};

int execute(struct proc proc) {
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		for(int i = 0; i < NUM_CHANS; i++) {
			if (i == proc.read_chan) {
				set_chan(&proc.chans[i], READ);
			} else if (i == proc.write_chan) {
				set_chan(&proc.chans[i], WRITE);
			} else {
				close_chan(&proc.chans[i]);
			}
		}
		if (proc.run(proc.argv) == EXIT_FAILURE) {
			if (proc.read_chan != UNUSED) {
				close_chan(&proc.chans[proc.read_chan]);
			}
			if (proc.write_chan != UNUSED) {
				close_chan(&proc.chans[proc.write_chan]);
			}
			exit(EXIT_FAILURE);
		}
	}
	return pid;
}

int main(int argc, char *argv[]) {
	/* Set up */

	// Declare the pipes
	struct chan chans[NUM_CHANS];
	for (int i = 0; i < NUM_CHANS; i++) {
		chans[i] = new_chan();
	}
	// Set up pfind proc
	struct proc pfind_proc;
	for (int i = 0; i < NUM_CHANS; i++) {
		pfind_proc.chans[i] = chans[i];
	}
	pfind_proc.run = pfind_run;
	pfind_proc.read_chan = UNUSED;
	pfind_proc.write_chan = PFIND_TO_SORT;
	pfind_proc.argv = argv;

	// Set up sort proc
	struct proc sort_proc;
	for (int i = 0; i < NUM_CHANS; i++) {
		sort_proc.chans[i] = chans[i];
	}
	sort_proc.run = sort_run;
	sort_proc.read_chan = PFIND_TO_SORT;
	sort_proc.write_chan = SORT_TO_PARENT;
	sort_proc.argv = argv;

	/* Run children */
	// run pfind
	int pfind_pid;
	pfind_pid = execute(pfind_proc);
	// run sort
	int sort_pid;
	sort_pid = execute(sort_proc);




	/* Use output of sort to print to STDOUT */
	// Pipe control
	close_chan(&chans[PFIND_TO_SORT]);
	set_chan(&chans[SORT_TO_PARENT], READ);
	// Read buffer

	int pfind_status;
	int sort_status;

	char b[BUF_SIZE];
	int n;
	int lines = 0;
	for (;;) {
		n = read(STDIN_FILENO, b, BUF_SIZE-1);
		if (n == -1) {
			fprintf(stderr, "Error: read() failed. %s.\n", strerror(errno));
		}
		if (n == 0) {
			break;
		}
		for (int i = 0; i < n; i++) {
			if (b[i] == '\n') {
				lines++;
			}
		}
		write(STDOUT_FILENO, b, n);
	}

	close_chan(&chans[SORT_TO_PARENT]);
	waitpid(pfind_pid, &pfind_status, 0);
	waitpid(sort_pid, &sort_status, 0);
	if (WEXITSTATUS(pfind_status) == 0) {
		printf("Total matches: %d\n", lines);
	}
}
