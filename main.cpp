#include <iostream>
#include <locale>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "socketaddr_to_str.h"
#include "create_server_socket.h"
#include "commands.h"

#include "statistics.h"
#include "FDIOAdapter.h"

#include "SPI.h"
#include "SPICommand.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <netinet/in.h>

void start_user_session_process(int server_sfd, int client_sfd) {
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

int main(int argc, char * argv[]) {
    
    int port = 18002;
    if (argc == 3) {
        if (strcmp(argv[1], "--port") == 0) {
            port = atoi(argv[2]);
        }
    } else {
        std::cout << "argc" << argc << std::endl;
    }

    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    int server_sfd = create_server_socket(port, true);
    
    
    struct sockaddr client_address;
    socklen_t client_address_length = sizeof(client_address);
    while(true) {
            int client_sfd = accept(server_sfd, &client_address, &client_address_length);
            std::cout << "client_sfd: " << client_sfd <<" connected " << sockaddr_str(client_address) << std::endl;
            start_user_session_process(server_sfd, client_sfd);
            std::cout << "Continuing to listen..." << std:: endl;
    }
    return 0;
}
