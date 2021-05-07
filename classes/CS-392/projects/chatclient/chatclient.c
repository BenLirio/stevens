#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "util.h"

int client_socket = -1;
char username[MAX_NAME_LEN + 1];
char inbuf[BUFLEN + 1];
char outbuf[MAX_MSG_LEN + 1];

int handle_stdin() {
	enum parse_string_t status;
	status = get_string(outbuf, MAX_MSG_LEN);
	switch(status) {

	case OK:
		if (strcmp("bye", outbuf) == 0) {
			printf("Goodbye.\n");
			return -1;
		}
		send(client_socket, outbuf, MAX_MSG_LEN, 0); // WARNING not error checking message send
		return 0;

	case TOO_LONG:
		printf("Sorry, limit your message to %d characters.\n", MAX_MSG_LEN);
		return 0;

	case NO_INPUT:
		return 0;

	default:
		fprintf(stderr, "get_string() should return one of {OK, TOO_LONG, NO_INPUT}\n");
		return -1;
	}

}
int handle_client_socket() {
	ssize_t n;
	n = recv(client_socket, inbuf, MAX_MSG_LEN, 0);
	switch(n) {
	case 0:
		fprintf(stderr, "Connection to server has been lost.\n");
		return -1;
		
	case -1:
		fprintf(stderr, "Warding: Failed to recieve incoming message. %s.\n",
			strerror(errno));
		return 0;
	default:
		inbuf[n] = '\0';
		if (strcmp("bye", inbuf) == 0) {
			printf("\nServer Initiated shutdown.\n");
			return -1;
		}
		printf("%s\n", inbuf);
		return 0;
		
	}
}

int main(int argc, char *argv[]) {
	int retval = EXIT_SUCCESS;
	ssize_t n;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int pton_ret;
	struct sockaddr_in server_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	memset(&server_addr, 0, addrlen);
	server_addr.sin_family = AF_INET;

	pton_ret = inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	if (pton_ret == 0) {
		fprintf(stderr, "Error: Invalid IP address '%s'.\n", argv[1]);
		return EXIT_FAILURE;

	}
	// Should check inet_pton for -1
	int port;
	if (parse_int(argv[2], &port, "Error: Port must be in range [1024, 65535].\n") == false) {
		return EXIT_FAILURE;
	}
	server_addr.sin_port = htons(port);

	for (;;) {
		// Some sketchy code here. Definilty double check
		printf("username: ");
		fflush(stdout);
		n = read(STDIN_FILENO, username, MAX_NAME_LEN+1);
		// Is \n a username
		if (n <= 1) {
			continue;
		}
		if (n > MAX_NAME_LEN) {
			printf("Sorry, limit your username to %d characters.\n", MAX_NAME_LEN);
			continue;
		}
		username[n-1] = '\0';
		break;
	}
	printf("Hello, %s. Let's try to connect to the server.\n", username);

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		fprintf(stderr, "Error: Failed to create socket. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) != 0) {
		fprintf(stderr, "Error: Failed to connect to server. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	n = recv(client_socket, inbuf, BUFLEN, 0);
	if (n == -1) {
		fprintf(stderr, "Error: Failed to recieve message from server. %s.\n",
			strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	if (n == 0) {
		fprintf(stderr, "All connections are busy. Try again later.\n");
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	inbuf[n] = '\0';

	printf("\n%s\n\n", inbuf);

	if (send(client_socket, username, strlen(username), 0) == -1) {
		fprintf(stderr, "Error: Failed to send username to server. %s.\n", strerror(errno));
		goto EXIT;
	}

	int fdmax;
	fd_set master;
	fd_set active_fds;
	FD_ZERO(&master);
	FD_ZERO(&active_fds);

	FD_SET(STDIN_FILENO, &master);
	fdmax = STDIN_FILENO;
	FD_SET(client_socket, &master);
	fdmax = client_socket > fdmax ? client_socket : fdmax;

	for (;;) {
		printf("[%s]: ", username);
		fflush(stdout);
		active_fds = master;
		if (select(fdmax+1, &active_fds, NULL, NULL, NULL) == -1) {
			fprintf(stderr, "Error: select failed. %s.\n", strerror(errno));
			retval = EXIT_FAILURE;
			goto EXIT;
		}
		for (int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &active_fds)) {
				if (i == STDIN_FILENO) {
					if (handle_stdin() != 0) {
						goto EXIT;
					}
				}
				if (i == client_socket) {
					if (handle_client_socket() == 0) {
						goto EXIT;
					}
				}
			}
		}
	}


	EXIT:
	close(client_socket);
	return retval;
}
