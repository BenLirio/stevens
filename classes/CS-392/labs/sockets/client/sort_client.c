#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#define BUFLEN 123

bool msgs_too_long(int argc, char **argv) {
		int cumulative_len = 0;
		for (int i = 0; i < argc; i++) {
			cumulative_len += strlen(argv[i]);
			if (i < argc - 1) {
				cumulative_len++;	
			}
			if (cumulative_len >= BUFLEN) {
				return true;
			}
		}
		return false;
}

int main(int argc, char* argv[]) {
	int client_socket = -1;
	int retval = EXIT_SUCCESS;
	int bytes_recvd;
	int ip_conversion;
	struct sockaddr_in server_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[BUFLEN];
	char *addr_str = "0.0.0.0";

	if (argc < 2) {
		fprintf(stderr, "Error. Must provide at least 1 string to sort.\n");
		return EXIT_FAILURE;
	}
	
	if (msgs_too_long(argc, argv)) {
		fprintf(stderr, "Error: At most %d characters can be sent, including '\\0'!\n", BUFLEN);
		retval = EXIT_FAILURE;
		goto EXIT;
	}


	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error: Failed to create socket. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
	}

	memset(&server_addr, 0, addrlen);
	server_addr.sin_family = AF_INET; // internet address family
	server_addr.sin_port = htons(3000); // server port, 16 bits


	// Convert character string into network address.
	ip_conversion = inet_pton(AF_INET, addr_str, &server_addr.sin_addr);
	if (ip_conversion == 0) {
		fprintf(stderr, "Error: Invalid IP address '%s'.\n", addr_str);
		retval = EXIT_FAILURE;
		goto EXIT;
	} else if (ip_conversion < 0) {
		fprintf(stderr, "Error: Failed to convert IP address. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	
	if (connect(client_socket, (struct sockaddr *) &server_addr, addrlen) < 0) {
		fprintf(stderr, "Error: Failed to connect to server. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	send(client_socket, "asdf", 4, 0);
	for (;;) {
		bytes_recvd = recv(client_socket, &buf, BUFLEN-1, 0);
		if (bytes_recvd < 0) {
			fprintf(stderr, "Error: Failed to recv message from server. %s.\n", strerror(errno));
			retval = EXIT_FAILURE;
			goto EXIT;
		}
		if (bytes_recvd == 0) {
			break;
		}
		buf[bytes_recvd] = '\0';
		printf("%s\n", buf);

	}

	EXIT:
	return retval;
}
