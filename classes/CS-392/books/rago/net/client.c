#include <sys/socket.h>

int main() {
	int socket_fd;
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
}
