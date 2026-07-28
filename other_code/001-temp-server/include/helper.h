#ifndef __HELPER_C__
#define __HELPER_C__

typedef union MyIPv4 {
	struct {
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
		uint8_t byte4;
	} components;
	struct in_addr sin_addr; //uint32_t sin_addr;
} my_ipv4_t;

void print_addrinfo(struct addrinfo * structData);

#endif
