//server
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main() {
	int socket_fd;
	struct sockaddr *address;
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	// Bind socket to address
	if (bind(socket_fd, address, sizeof(address)) == -1) {
		fprintf(stdout, "Error: failed to bind socket to address. %s.\n", strerror(errno));
	}
	if (connect(socket_fd, address, sizeof(address)) == -1) {
		fprintf(stdout, "Error: failed to connect socket to address. %s\n", strerror(errno));
	}
}
