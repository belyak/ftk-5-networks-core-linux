#include <iostream>
#include <locale>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "socketaddr_to_str.h"
#include "create_server_socket.h"

#include "statistics.h"
#include "FDIOAdapter.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <netinet/in.h>

int main() {

	int server_sfd = create_server_socket(18009, true);
	struct sockaddr client_address;
	socklen_t client_address_length = sizeof(client_address);
	int client_sfd = accept(server_sfd, &client_address, &client_address_length);
	std::cout << "client_sfd: " << client_sfd <<" connected " << sockaddr_str(client_address) << std::endl;
	return 0;
}
