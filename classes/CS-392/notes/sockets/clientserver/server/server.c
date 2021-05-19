#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>

#define PORT "3000"
#define BUFLEN 4

int main() {

	// Create address
	struct addrinfo* res;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me
	if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
		fprintf(stderr, "Error: getaddrinfo() failed. %s.\n", strerror(errno));
	}

	// make a socket, bind it, and listen on it:
	int sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock_fd == -1) {
		fprintf(stderr, "Error: socket() failed. %s.\n", strerror(errno));
	}
	if (bind(sock_fd, res->ai_addr, res->ai_addrlen) != 0) {
		fprintf(stderr, "Error: bind() failed. %s.\n", strerror(errno));
	}
	if (listen(sock_fd, 0) != 0) {
		fprintf(stderr, "Error: listen() failed. %s.\n", strerror(errno));
	}

	for (;;) {
		int connection_fd = accept(sock_fd, res->ai_addr, &res->ai_addrlen);
		if (connection_fd == -1) {
			fprintf(stderr, "Error: accept() failed. %s.\n", strerror(errno));
		}
		printf("Connection\n");
		ssize_t n;
		char buf[BUFLEN];
		for(;;) {
			n = recv(sock_fd, buf, BUFLEN, 0);
			if (n < 0) {
				fprintf(stderr, "Error: recv failed. %s.\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if (n == 0) {
				break;
			}
			if (write(STDOUT_FILENO, buf, n) != n) {
				fprintf(stderr, "Error: write() failed. %s.\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}
}
