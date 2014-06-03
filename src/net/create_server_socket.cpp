#include "create_server_socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include <iostream>

/**
 * метод для создания серверного сокета, слушающего указанный TCP порт.
 * 
 * @param port порт для клиентских соединений
 * @param is_blocking блокирующий режим сокета
 * @return дескриптор сокета либо -1 в случае ошибки
 */
int create_server_socket(int port, bool is_blocking) {
	struct sockaddr_in server_address_in;

	server_address_in.sin_family = AF_INET;
	server_address_in.sin_port = htons(port);
	server_address_in.sin_addr.s_addr = htonl( INADDR_ANY );
	struct sockaddr * server_address = (struct sockaddr *) &server_address_in;

	int socket_type_argument = is_blocking ? SOCK_STREAM : SOCK_STREAM | SOCK_NONBLOCK;
	int server_sfd = socket(AF_INET, socket_type_argument, 0);

	if (server_sfd < 0) {
		int _error = errno;
		std::cout << "Error creating server socket (errno: " << _error << ")" << std::endl;
		return -1;
	}

	int bind_result = bind(server_sfd, server_address, sizeof(server_address_in));
	if (bind_result < 0) {
		int _error = errno;
		std::cout << "Error bounding server socket (errno: " << _error << ")" << std::endl;
		return -1;
	}

	int listen_result = listen(server_sfd, BACKLOG);
	if (listen_result) {
		int _error = errno;
		std::cout << "Error during listen call (errno: " << _error << ")" << std::endl;
		return -1;
	}

	return server_sfd;
}