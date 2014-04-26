#include "socketaddr_to_str.h"

#include <stdio.h>
#include <string.h>
#include "netinet/in.h"

#define ADDR_AND_PORT_STR_MAX_LEN (3+1)*4+5+1

char * sockaddr_str(const struct sockaddr & addr) {

	static char buffer[ADDR_AND_PORT_STR_MAX_LEN];

	struct sockaddr_in * s_in = (struct sockaddr_in *) & addr;
	unsigned int port = ntohs(s_in->sin_port);
	long int address_lint = ntohl(s_in->sin_addr.s_addr);
	struct inet4_addr {
		unsigned char b4;
		unsigned char b3;
		unsigned char b2;
		unsigned char b1;
	};
	struct inet4_addr * address;
	address = (struct inet4_addr*) & address_lint;
	memset((void *)buffer, 0, sizeof(buffer));

	sprintf(buffer, "%d.%d.%d.%d:%d", address->b1, address->b2, address->b3, address->b4, port);
	return buffer;
}


