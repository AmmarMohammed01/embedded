# NOTES

## ABOUT

## ISSUES

### Segmentation Fault

Trying to print out struct addrinfo.
```C
void print_addrinfo(struct addrinfo * structData) {
	do {
		printf("ai_flags: %d\n", structData->ai_flags);
		printf("ai_family: %d\n", structData->ai_family);
		printf("ai_socktype: %d\n", structData->ai_socktype);
		printf("ai_protocol: %d\n", structData->ai_protocol);
		printf("ai_addrlen: %u\n", structData->ai_addrlen);
		printf("ai_addr: %p\n", structData->ai_addr);
		printf("ai_canonname: %s\n", structData->ai_canonname);
		printf("ai_next: %p\n", structData->ai_next);
		printf("\n");
		structData = structData->ai_next;
	} while(structData->ai_next != NULL);
}
```
- I used LLDB to find out that when reading ```struct addrinfo hints```
- I move to the next of hints. The next node is 0x00, meaning NULL, there is no node.
- Then, after leaving first iteration of do while loop, I try to read the NULL nodes next.
- Then, segmentation fault.

MY SOLUTION:
- I just created an infinite while loop and escape when next node is NULL
```C
while(1) {
	printf("ai_flags: %d\n", structData->ai_flags);
	printf("ai_family: %d\n", structData->ai_family);
	printf("ai_socktype: %d\n", structData->ai_socktype);
	printf("ai_protocol: %d\n", structData->ai_protocol);
	printf("ai_addrlen: %u\n", structData->ai_addrlen);
	printf("ai_addr: %p\n", structData->ai_addr);
	printf("ai_canonname: %s\n", structData->ai_canonname);
	printf("ai_next: %p\n", structData->ai_next);
	printf("\n");
	if (structData->ai_next == NULL) {
		break;
	}
	structData = structData->ai_next;
}
```

Usual way to traverse Linked-List
```C
while (node != NULL) {
    // use node
    node = node->next;
}
```

### Understanding output

```markdown
Printing struct addrinfo: hints
-------------------------------
ai_flags: 1
ai_family: 0
ai_socktype: 1
ai_protocol: 0
ai_addrlen: 0
ai_addr: 0x0
ai_canonname: (nulL)
ai_next: 0x0

Printing struct addrinfo: servinfo
----------------------------------
ai_flags: 0
ai_family: 30
ai_socktype: 1
ai_protocol: 6
ai_addrlen: 28
ai_addr: 0x6000003400c0
ai_canonname: (nulL)
ai_next: 0x600000d40000

ai_flags: 0
ai_family: 2
ai_socktype: 1
ai_protocol: 6
ai_addrlen: 16
ai_addr: 0x60000014c000
ai_canonname: (nulL)
ai_next: 0x0
```

Can be found in sys/socket.h

The (*) options below are listed just to know, but wasn't observed in output.

ai_family
| value | meaning   |
| ----- | --------- |
| 0     | AF_UNSPEC |
| 30    | AF_INET6  |
| 2     | AF_INET   |

socktype
| value | meaning     |
| ----- | ----------- |
| 1     | SOCK_STREAM |
| *2    | SOCK_DGRAM  |

protocol - I looked up protocol families, which in Mac SDK took me back to address families??? (read line below)
netdb.h: 0 or IPPROTO_xxx for IPv4 and IPv6 
/etc/protocols
| value | meaning   |
| ----- | --------- |
| 0     | IP        |
| 6     | TCP       |
| *17   | UDP       |

Found in netdb.h
ai_flags
| value | meaning   |
| ----- | --------- |
| 1     | AI_PASSIVE     |
| *2    | AI_CANONNAME   |
| *4    | AI_NUMERICHOST |

### printf formats
Found in man printf, format section.

PORT Numbers
/etc/services

Got file descriptor using socket():
- man socket
- Passed in servinfo address information

Binding a port to our socket, so later server knows where to listen
- man 2 bind
- passing addrinfo's field storing struct sockaddr, which can be struct sockaddr_in, containing ip address and port

Allow the server port to open, listen to incoming connections, place them in queue until server ready to accept()
- man listen
- pass socket file descriptor and # of backlog for queue


