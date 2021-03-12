#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 128

int main() {
	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = IPPROTO_IP;
	printf("domain: %d\n", domain);
	printf("type: %d\n", type);
	printf("protocol: %d\n", protocol);
	int s = socket(domain, type, protocol);

	printf("Socket %d\n", s);
	char b[BUFSIZE];
	for (int i = 0; i < BUFSIZE; i++) {
		b[i] = i;
	}
	//send(s, b, BUFSIZE, 0);
	if (close(s) == -1) {
		printf("failed to close\n");
	}
	return 0;
}
