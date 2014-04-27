#include "SPI.h"
#include "lgs_constants.h"
#include "create_message.h"
#include "SPICommand.h"
#include "CommandResponse.h"

#include <iostream>
#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <map>


char * get_banner() {
    static char buffer[MAX_LINE_LENGTH] = "\0";
    if (buffer[0] == '\0') {
        sprintf(buffer, SERVER_BANNER, SERVER_VERSION);
    }
    return buffer;
}

SPI::SPI() {}
SPI::~SPI() {}

char * SPI::read_line() {
    static char buffer[MAX_LINE_LENGTH];
    bool correct_line_received = false;
    while (!correct_line_received) {
        memset(buffer, 0, sizeof(buffer));
        int offset = 0;
        bool read_successfull = true;
        int delimiter_found = false;
        while (!delimiter_found && read_successfull && offset < sizeof(buffer)) {
            
            buffer[offset] = this->read_byte(read_successfull);
            
            if (offset >= 2) {
                if (buffer[offset - 1] == LINES_SEPARATOR[0]) {
                    if (buffer[offset] == LINES_SEPARATOR[1]) {
                        delimiter_found = true;
                        correct_line_received = true;
                        buffer[offset - 1] = '\0';
                    }
                }
            }
            offset++;
        };
    }
    return buffer;
}

std::string SPI::first_word(std::string & line) {
    static std::string result;
    result.clear();
    
    std::size_t space_pos = line.find(' ');
    if (std::string::npos != space_pos){
        result = line.substr(0, space_pos);
    } else {
        result = line;
    }
    return result;
}

void SPI::start() { 
    
    std::map<std::string, SPICommand*> registered_commands;
    
    #define REGISTER_CMD(CMD_CLS) { SPICommand * cmd = new CMD_CLS(); \
    registered_commands[cmd->get_keyword()] = cmd; }
    
    REGISTER_CMD(VersionCommand);
    REGISTER_CMD(ExitCommand);
    
    ExitCommand * exitCommand = new ExitCommand();
    
    
    // отправка приветственного сообщения
    this->send_message(200, get_banner());
    
    bool exit_called = false;
    while (!exit_called) {
        std::string line(this->read_line());
            std::cout << "Got line: " << line << std::endl;
            std::string possible_command = this->first_word(line);
            std::cout << "Possible command:`" << possible_command << "`" << std::endl;

            if (registered_commands.find(possible_command) != registered_commands.end()) {
                SPICommand * command = registered_commands[possible_command];
                std::cout << "going to run " << command->get_keyword() << std::endl;
                CommandResponse response = command->run();
                this->send_message(response);
                if (command->get_keyword() == exitCommand->get_keyword()) {
                    exit_called = true;
                }
            }
    }
}

SocketSPI::SocketSPI(int client_socket_fd) {
    this->client_sfd = client_socket_fd;
}

SocketSPI::~SocketSPI() { close(client_sfd); }

void SocketSPI::send_message(const int code, const char* data) {
    char * msg = create_message(code, data);
    send(this->client_sfd, (void *) msg, strlen(msg), 0);
}

void SocketSPI::send_message(CommandResponse& response) {
    char * msg = response.raw();
    send(this->client_sfd, (void*) msg, strlen(msg), 0);
}

unsigned char SocketSPI::read_byte(bool& read_ok) {
    static char buffer[2];
    memset((void*)buffer, 0, sizeof(buffer));
    int code = recv(this->client_sfd, buffer, 1, 0);
    read_ok = code != -1;
    return buffer[0];
}