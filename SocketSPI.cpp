#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>

#include "SocketSPI.h"
#include "create_message.h"

SocketSPI::SocketSPI(int client_socket_fd) {
    this->client_sfd = client_socket_fd;
}

SocketSPI::~SocketSPI() { 
    close(client_sfd); 
}

void SocketSPI::send_message(const int code, const char* data) {
    char * msg = create_message(code, data);
    send(this->client_sfd, (void *) msg, strlen(msg), 0);
}

void SocketSPI::send_message(CommandResponse& response) {
    char * msg = response.raw();
    int send_result = send(this->client_sfd, (void*) msg, strlen(msg), 0);
    if (send_result == -1) {
        perror("send");
    }
}

unsigned char SocketSPI::read_byte(bool& read_ok) {
    static char buffer[2];
    memset((void*)buffer, 0, sizeof(buffer));
    int code = recv(this->client_sfd, buffer, 1, 0);
    read_ok = code != -1;
    return buffer[0];
}
