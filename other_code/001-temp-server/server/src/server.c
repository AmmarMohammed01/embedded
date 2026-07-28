#include <sys/types.h>
#include <sys/socket.h> //getaddrinfo(), AF_INET6, socket(), bind(), listen(), accept()
#include <netdb.h> //struct addrinfo
#include <string.h> //memset
#include <stdio.h> //fprintf()
#include <stdlib.h> //exit()
#include <arpa/inet.h> //inet_ntop()
#include <unistd.h> //close()

#include "helper.h"

#define BACKLOG 5 // # of connections to this server's socket

int main() {
	//setup IP and PORT to listen on getaddrinfo, struct addrinfo
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo; // will point to results

	memset(&hints, 0, sizeof hints); // make sure struct is empty
	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6 
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets 
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me

	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "gai error: %s\n", gai_strerror(status));
		exit(1);
	}

	/*
	printf("Printing struct addrinfo: hints\n");
	printf("-------------------------------\n");
	print_addrinfo(&hints);

	printf("Printing struct addrinfo: servinfo\n");
	printf("----------------------------------\n");
	print_addrinfo(servinfo);
	*/

	//create a socket file descriptor, socket(domain, type, protocol)
	//should not return -1
	//int sockfd = socket(PF_INET, SOCK_STREAM, 6); //6 for tcp
	int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol); //open socket
	printf("sockfd: %d\n", sockfd);

	bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen); //bind a port, passing in sockaddr_in which includes sin_port

	//listen to incoming connections, BACKLOG is # of connections that wait in a queue until accept()
	listen(sockfd, BACKLOG);

	//accept an incoming connection
	int new_sockfd;
	struct sockaddr_storage incoming_addr;
	socklen_t incoming_addr_size = sizeof incoming_addr;
	new_sockfd = accept(sockfd, (struct sockaddr*)&incoming_addr, &incoming_addr_size);
	printf("new_sockfd: %d\n", new_sockfd);

	close(sockfd); //close socket

	freeaddrinfo(servinfo); //free dynamically allocated mem for servinfo

	return 0;
}

