#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "net/create_server_socket.h"
#include "net/socketaddr_to_str.h"
#include "spi/ConsoleSPI.h"
#include "spi/SocketSPI.h"

using std::endl;
using std::cout;

/**
 * Вывод сообщения о неверных аргументах командной строки и выход.
 */
void p_incorrect_arguments() {
    cout << "Please specify mode to run or --help for getting help" << endl;
    exit(1);    
}

/**
 * Вывод справки об использовании аргументов командной строки и выход.
 */
void p_help() {
    cout << "Sample usage:" << endl << endl <<
            "xinetd mode:" << endl <<
            "lgs --mode xinetd" << endl <<
            "standalone mode:" << endl <<
            "lgs --mode standalone" << endl <<
            "also you can use -m instead od --mode" << endl;
    exit(0);
}

/**
 * Создает копию процесса, в которой инициализирует SPI сокетом входящего
 * клиентского соединения и передает ему управление. После завершения работы 
 * SPI завершает работу процессса.
 * 
 * @param server_sfd дескриптор серверного сокета
 * @param client_sfd дескриптор подключенного клиентского сокета.
 */
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

/**
 * Начало работы в режиме консольного приложение (предполагается запуск через
 * службу xinetd. Осуществляется запуск SPI в том же потоке, завершение его 
 * работы означает завершение работы программы, т.к. xinetd запускает новый 
 * экземпляр приложения для каждого нового входящего запроса на подключение.
 */
void start_console_mode() {
    SPI * spi = new ConsoleSPI();
    spi->start();
}

/**
 * Начало работы в режиме многопоточного сервера. В бесконечном цикле сервер
 * принимает входящие соединения и вызывает для обработки каждого функцию
 * start_remote_session.
 * 
 * @param port порт на котором будет запущен сервер
 */
void start_server_mode(int port) {
    int server_sfd = -1;
    while (-1 == (server_sfd = create_server_socket(port, true))) {
        port++;
    }
    std::cout << "Server started at port " << port << std::endl;
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

/**
 * Основная фуекция сервера (точка входа).
 * Запускает сервер при передачи ему корректного режима запуска, либо
 * выводит справка при запуске с единственным аргументом --help,
 * либо выводит сообщение о неверных аргументах и выходит с кодом 1.
 * 
 * @param argc количество аргументов командной строки
 * @param argv массив строк - аргументов командной строки
 * @return 
 */
int main(int argc, char** argv) {
    
    enum RunMode { XINETD, STANDALONE } runMode;

    if (argc == 1) {
        p_incorrect_arguments();
    } else if (argc == 2) {
        if (argv[1] == "--help") {
            void p_help();
        } 
    } else if (argc == 3) {
        if ((strcmp(argv[1], "--mode") == 0) || (strcmp(argv[1], "-m") == 0)) {
            if (strcmp(argv[2], "xinetd") == 0) {
                runMode = XINETD;
            } else if (strcmp(argv[2], "standalone") == 0) {
                runMode = STANDALONE;
            } else {
                p_incorrect_arguments();
            }
        } else {
            p_incorrect_arguments();
        }
    } else {
        p_incorrect_arguments();
    }
    
    if (runMode == XINETD) {
        start_console_mode();
    } else if (runMode == STANDALONE) {
        start_server_mode(18000);
    }
    
    return 0;
}

