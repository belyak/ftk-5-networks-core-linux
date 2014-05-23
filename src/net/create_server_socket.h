#ifndef CREATE_SERVER_SOCKET_H_
#define CREATE_SERVER_SOCKET_H_

#define BACKLOG 100

int create_server_socket(int port, bool is_blocking);

#endif /* CREATE_SERVER_SOCKET_H_ */
