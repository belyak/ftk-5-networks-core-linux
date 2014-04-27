#include "SPI.h"
#include "lgs_constants.h"

#include <iostream>
#include <string.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

char * read_line(int fd) {
    static char buffer[MAX_LINE_LENGTH];
    bool correct_line_received = false;
    while (!correct_line_received) {
        memset(buffer, 0, sizeof(buffer));
        int offset = 0;
        int code;
        int delimiter_found = false;
        while (!delimiter_found and code != -1 and offset < sizeof(buffer)) {
            
            code = recv(fd, buffer + offset, 1, 0);
            if (offset >= 2) {
                if (buffer[offset - 1] == LINES_SEPARATOR[0]) {
                    if (buffer[offset] == LINES_SEPARATOR[1]) {
                        delimiter_found = true;
                        correct_line_received = true;
                    }
                }
            }
            offset++;
        };
    }
    return buffer;
}

char * create_message(const int code, const char * msg) {
    static char buff[MAX_LINE_LENGTH];
    memset(buff, 0, sizeof(buff));
    sprintf(buff, "%d %s%s", code, msg, LINES_SEPARATOR);
    return buff;
}

void send_message(const int fd, const int code, const char * message) {
    char * msg = create_message(code, message);
    send(fd, (void *) msg, strlen(msg), 0);
}

char * get_banner() {
    static char buffer[MAX_LINE_LENGTH] = "\0";
    if (buffer[0] == '\0') {
        sprintf(buffer, SERVER_BANNER, SERVER_VERSION);
    }
    return buffer;
}

void user_session(int client_sfd) {
    send_message(client_sfd, 200, get_banner());
    std::cout << "GOT LINE: " << read_line(client_sfd) << std::endl;
}
