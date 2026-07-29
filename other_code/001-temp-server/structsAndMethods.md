# SOCKET structs

## Confusion

There are SO many structs.

Maybe it will be easier if I think about what is needed in general.

Need an IP address and a PORT number.
- Use getaddrinfo()

## Structs

### Address Info Struct
---

Can be found in netdb.h

```C
struct addrinfo {
    int              ai_flags;      // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;     // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;   // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;   // use 0 for "any"
    size_t           ai_addrlen;    // size of ai_addr in bytes
    struct sockaddr *ai_addr;       // struct sockaddr _in or _in6
    char            *ai_canonname;  // full canonical hostname

    struct addrinfo *ai_next;       // linked list, next node
};
```


### The Main Struct
---
Can be found in netinet/in.h

```C
struct sockaddr {
	unsigned short	sa_family; //address family, AF_INET or AF_INET6
	char		sa_data[14]; //14 bytes of protocol address
}; //16 BYTES
```


#### IPv4 Version of sockaddr
---

```C
struct sockaddr_in {
	short int		sin_family;	//[2B] Address family, AF_INET
	unsigned short int	sin_port;	//[2B] Port number
	struct in_addr		sin_addr;	//[4B] Internet address
	unsigned char		sin_zero[8];	//[8B] Same size as struct sockaddr
}; //16 BYTES
```

```
IPv4 uses 4 byte addresses.
Each byte is 0 to 255
Example 192.168.4.1
1st byte: 192,	2nd byte: 168,	3rd byte: 4,	4th byte: 1
```

ALSO THE PORT INFO IS STORED HERE IN THE sockaddr_in.sin_port, or inside of sockaddr.sa_data

```C
struct in_addr {
	uint32_t s_addr; //4 bytes = 32 bits
};  //[4B]
```


#### IPv6 Version of sockaddr
---

```C
struct sockaddr_in6 {
	u_int16_t	sin6_family;	//[2B] address family, AF_INET6
	u_int16_t	sin6_port;	//[2B] port, Network Byte Order
	u_int32_t	sin6_flowinfo;	//[4B] IPv6 flow information
	struct in6_addr	sin6_addr;	//[16B] IPv6 address
	u_int32_t	sin6_scope_id;	//[4B] Scope ID
}; //28 BYTES
```

IPv6 has address & port number. What is scope ID & flow info?

```C
//WHY CREATE A STRUCT FOR ONE VARIABLE?
struct in6_addr {
	unsigned char	s6_addr[16]; //IPv6 address
};
```


### Storage Struct
---

```C
struct sockaddr_storage {
    sa_family_t ss_family;  // address family

    // all this is padding, implementation specific, ignore it:
    char    __ss_pad1[_SS_PAD1SIZE];
    int64_t __ss_align;
    char    __ss_pad2[_SS_PAD2SIZE];
};
```


## Functions

### getaddrinfo() - prepare to launch!

PROVIDE: Three (3) input parameters.
RECEIVE: Linked-list ```res```
RETURNS: 0 on success, else error.

```C
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, // e.g. "www.example.com" or IP 
		const char *service, // e.g. "http" or port number (80)
		const struct addrinfo *hints,
		struct addrinfo **res);
```
