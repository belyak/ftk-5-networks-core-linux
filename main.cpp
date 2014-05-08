#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

#include "create_server_socket.h"
#include "socketaddr_to_str.h"
#include "ConsoleSPI.h"
#include "SocketSPI.h"

using std::endl;
using std::cout;

void p_incorrect_arguments() {
    cout << "Please specify mode to run or --help for getting help" << endl;
    exit(1);    
}

void p_help() {
    cout << "Sample usage:" << endl << endl <<
            "xinetd mode:" << endl <<
            "lgs --xinetd" << endl <<
            "standalone mode:" << endl <<
            "lgs --server" << endl;
}

void start_remote_session(int server_sfd, int client_sfd) {
    pid_t pid;
        if ( (pid = fork()) == 0) {
            std::locale::global(std::locale("ru_RU.UTF-8"));
            close(server_sfd);

            SocketSPI * spi = new SocketSPI(client_sfd);
            spi->start();
            std::cout << "User session terminates in 2 seconds." << std::endl;
            sleep(2);
            delete spi;
            exit(0);
        } else {
            close(client_sfd);
        }

}

void start_console_mode() {
    SPI * spi = new ConsoleSPI();
    spi->start();
}

void start_server_mode() {
    int server_sfd = create_server_socket(18000, true);
    
    struct sockaddr client_address;
    socklen_t client_address_length = sizeof(client_address);
    while(true) {
        int client_sfd = accept(server_sfd, &client_address, &client_address_length);
        std::cout << "client with socket descriptor " << client_sfd <<
                    " connected " << sockaddr_str(client_address) << std::endl;
        start_remote_session(server_sfd, client_sfd);
        std::cout << "Continuing to listen..." << std:: endl;
    }    
}

int main(int argc, char** argv) {
    
    enum RunMode { XINETD, STANDALONE } runMode;

    if (argc == 1) {
        p_incorrect_arguments();
    } else if (argc == 2) {
        if (argv[1] == "--help") {
            void p_help();
        } else if (strcmp(argv[1], "--xinetd") == 0) {
            runMode = XINETD;
        } else if (strcmp(argv[1], "--server") == 0) {
            runMode = STANDALONE;
        } else {
            p_incorrect_arguments();
        }
    } else {
        p_incorrect_arguments();
    }
    
    if (runMode == XINETD) {
        start_console_mode();
    } else if (runMode == STANDALONE) {
        start_server_mode();
    }
    
    return 0;
}

