#include <sys/socket.h> //AF_INET, AF_INET6
#include <arpa/inet.h> //inet_ntop()
#include <netdb.h> //struct addrinfo
#include <stdio.h> //printf, NULL

#include "helper.h"

void print_addrinfo(struct addrinfo * structData) {
	while(structData != NULL) {
		printf("ai_flags: %d\n", structData->ai_flags);
		printf("ai_family: %d\n", structData->ai_family);
		printf("ai_socktype: %d\n", structData->ai_socktype);
		printf("ai_protocol: %d\n", structData->ai_protocol);
		printf("ai_addrlen: %u\n", (unsigned)structData->ai_addrlen);
		printf("ai_addr: %p\n", (void *)structData->ai_addr);
		printf("ai_canonname: %s\n", structData->ai_canonname ? structData->ai_canonname : "(nulL)");
		printf("ai_next: %p\n", (void *)structData->ai_next);
		printf("\n");

		if(structData->ai_family == AF_INET6) { //INET6 - 30
			printf("\tsin6_family: %u\n", ((struct sockaddr_in6 *)structData->ai_addr)->sin6_family );
			printf("\tsin6_port: %u\n", ((struct sockaddr_in6 *)structData->ai_addr)->sin6_port );
			printf("\tsin6_flowinfo: %u\n", ((struct sockaddr_in6 *)structData->ai_addr)->sin6_flowinfo );
			//printf("\tsin6_addr: %s\n", ((struct sockaddr_in6 *)structData->ai_addr)->sin6_addr.s6_addr ); //won't work because 16 raw bytes of binary, not printable characters

			char addr_str[INET6_ADDRSTRLEN];
			struct sockaddr_in6 *sa = (struct sockaddr_in6 *)structData->ai_addr;
			inet_ntop(AF_INET6, &sa->sin6_addr, addr_str, sizeof(addr_str));
			printf("\tsin6_addr: %s\n", addr_str);

			printf("\tsin6_scope_id: %u\n", ((struct sockaddr_in6 *)structData->ai_addr)->sin6_scope_id );
		}
		else if (structData->ai_family == AF_INET) { //INET - 2
			printf("\tsin_family: %u\n", ((struct sockaddr_in *)structData->ai_addr)->sin_family ); //unsigned int
			printf("\tsin_port: %hu\n", ((struct sockaddr_in *)structData->ai_addr)->sin_port); //sin_port - unsigned short int
			//printf("sin_addr: %u\n", ((struct sockaddr_in *)structData->ai_addr)->sin_addr); //sin_addr - struct in_addr - uint32_t
			//sin_zero - unsigned char, don't need to print

			my_ipv4_t ip1 = { 
				.sin_addr = (struct in_addr)( ((struct sockaddr_in *)structData->ai_addr)->sin_addr )
			};
			/*
			printf("\t1st Byte: %u\n", ip1.components.byte1);
			printf("\t2nd Byte: %u\n", ip1.components.byte2);
			printf("\t3rd Byte: %u\n", ip1.components.byte3);
			printf("\t4th Byte: %u\n", ip1.components.byte4);
			*/
			printf("\tIP = %u.%u.%u.%u\n", ip1.components.byte1, ip1.components.byte2, ip1.components.byte3, ip1.components.byte4);

			/*
			char ip[INET_ADDRSTRLEN];
			struct sockaddr_in *sin = (struct sockaddr_in *)structData->ai_addr;
			inet_ntop(AF_INET, &sin->sin_addr, ip, sizeof(ip));
			printf("IP = %s\n", ip);
			*/
		}

		structData = structData->ai_next;
	}
}
