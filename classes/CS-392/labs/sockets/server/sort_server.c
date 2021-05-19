#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdbool.h>

#define BUFLEN 1246
#define PORT 3000

int main() {
	int server_socket = -1;
	int client_socket = -1;
	int retval = EXIT_SUCCESS;
	int bytes_recvd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[BUFLEN];

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error: Failed to create socket. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	memset(&server_addr, 0, addrlen);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server_socket, (struct sockaddr *)&server_addr, addrlen) < 0) {
		fprintf(stderr, "Error: Failed to bind socket to port %d. %s.\n", PORT, strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	if (listen(server_socket, SOMAXCONN) < 0) {
		fprintf(stderr, "Error: Failed to listen for incoming connections. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	printf("Sorting server is up and running on port %d...\n", ntohs(server_addr.sin_port));
	while (true) {
		if ((client_socket =
			accept(server_socket, (struct sockaddr *)&client_addr, &addrlen)) < 0) {
				fprintf(stderr, "error: Failed to accept incoming connection. %s.\n", strerror(errno));
				retval = EXIT_FAILURE;
				goto EXIT;
			}
		if ((bytes_recvd = recv(client_socket, &buf, BUFLEN-1, 0)) < 0) {
			fprintf(stderr, "Error: Failed to recieve message from client %s. %s.\n",
				inet_ntoa(client_addr.sin_addr), strerror(errno));
			retval = EXIT_FAILURE;
			goto EXIT;
		}
		buf[bytes_recvd] = '\0';
		printf("Recieved following from client: %s\n", buf);

		if (send(client_socket, buf, bytes_recvd, 1) < 0) {
			fprintf(stderr, "Error: Failed to send message to client %s. %s.\n", 
				inet_ntoa(client_addr.sin_addr), strerror(errno));
		}
	}
	EXIT:
	return retval;
}

