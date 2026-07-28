#include <sys/types.h>
#include <sys/socket.h> //getaddrinfo(), AF_INET6
#include <netdb.h> //struct addrinfo
#include <string.h> //memset
#include <stdio.h> //fprintf()
#include <stdlib.h> //exit()
#include <arpa/inet.h> //inet_ntop()

#include "helper.h"

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

	printf("Printing struct addrinfo: hints\n");
	printf("-------------------------------\n");
	print_addrinfo(&hints);

	printf("Printing struct addrinfo: servinfo\n");
	printf("----------------------------------\n");
	print_addrinfo(servinfo);

	return 0;
}

