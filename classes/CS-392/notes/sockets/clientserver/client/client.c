#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>

#define HOST "0.0.0.0"
#define PORT "3000"

int main() {
	// Get the address
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	if (getaddrinfo(HOST, PORT, &hints, &res) != 0) {
		fprintf(stderr, "Error: getaddrinfo() failed. %s.\n", strerror(errno));
	}

	// Create the socket
	int sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock_fd == -1) {
		fprintf(stderr, "Error: socket() failed. %s.\n", strerror(errno));
	}

	// Connect
	if (connect(sock_fd, res->ai_addr, res->ai_addrlen) != 0) {
		fprintf(stderr, "Error: connection failed. %s.\n", strerror(errno));
	}
	char* msg = "hello";
	ssize_t n;
	n = send(sock_fd, msg, strlen(msg), 0);
	if (n != strlen(msg)) {
		fprintf(stderr, "Message failed\n");
	}
}
