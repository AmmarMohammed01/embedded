#include <sys/types.h>
#include <sys/socket.h> //socket(), connect()
#include <netdb.h> //getaddrinfo()

#include <string.h> //memset()
#include <stdio.h> //printf()

int main() {
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; //either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("localhost", "3490", &hints, &res);
	//think for a moment: why an address to the pointer res? I know res can be a linked-list.
	//also what should the address be here to connect to my server.c code? 0.0.0.0 means all interfaces on the computer. Computer can have an IP address via Wi-Fi and Ethernet.

	//create a socket
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	//connect
	connect(sockfd, res->ai_addr, res->ai_addrlen);

	//receive data from server
	int data_len = 50;
	char data[data_len];
	int bytesReceived = recv(sockfd, data, data_len, 0); //if 0, connection has closed. if -1, then error.
	printf("Server told me: %s\n", data);
	printf("I received %d bytes.\n", bytesReceived);

	return 0;
}
