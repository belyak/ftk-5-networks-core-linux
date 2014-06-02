#include "SPI.h"
#include "../lgs_constants.h"
#include "create_message.h"
#include "commands/SPICommand.h"
#include "commands/CommandResponse.h"

#include <iostream>
#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


#include <map>
#include <sstream>


std::wstring get_banner(RegisteredCommands & registered_commands) {
    std::wstringstream ws;
    // Начало сообщения
    ws << SERVER_BANNER_P1 << SERVER_VERSION << SERVER_BANNER_P2;
    // список поддерживаемых комманд:
    ws << L" SC:";
    bool firstCmd = true;
    for (RegisteredCommands::iterator i = registered_commands.begin(); i != registered_commands.end(); i++) {
        std::string s_mnemonic =  (*i).first;
        std::wstring mnemonic(s_mnemonic.begin(), s_mnemonic.end());
        if (firstCmd) {
            firstCmd = false;
        } else {
            ws << L",";
        }
        ws << mnemonic;
    }
    ws << L".";
    // захардкодим список режимов передачи:
    ws << L" SM:plain.";
    return ws.str();
}

SPI::SPI() {}
SPI::~SPI() {}

char * SPI::read_line() {
    static char buffer[MAX_LINE_LENGTH];
    bool correct_line_received = false;
    int offset = 0;
    while (!correct_line_received) {
        memset(buffer, 0, sizeof(buffer));
        offset = 0;
        bool read_successfull = true;
        int delimiter_found = false;
        while (!delimiter_found && read_successfull && offset < sizeof(buffer)) {
            
            char byte_in = this->read_byte(read_successfull);
            
            if (offset == 0) {
                if (byte_in == CRLF[0] || byte_in == CRLF[1]) {
                        continue;
                }
            }
            
            buffer[offset] = byte_in;
            
            if (offset >= 2) {
                if (buffer[offset - 1] == CRLF[0]) {
                    if (buffer[offset] == CRLF[1]) {
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
   
    Statistics statistics(L"Current");
    encoder.setEncoding();
   
    RegisteredCommands registered_commands = init_registered_commands(statistics, encoder, this);
    // отправка приветственного сообщения
    CommandResponse bannerResponse(200, get_banner(registered_commands));
    this->send_message(bannerResponse);
    
    bool exit_called = false;
    while (!exit_called) {
        std::string line(this->read_line());
            std::cout << "Got line: " << line << std::endl;
            std::string possible_command = this->first_word(line);
            std::cout << "Possible command:`" << possible_command << "`" << std::endl;

            if (registered_commands.find(possible_command) != registered_commands.end()) {
                SPICommand * command = registered_commands[possible_command];
                std::cout << "going to run " << command->get_keyword() << std::endl;
                command->set_current_line(line);
                CommandResponse response = command->run();
                std::cout << "got response" << std::endl;
                this->send_message(response);
                if (command->get_keyword() == std::string("exit")) {
                    exit_called = true;
                }
            }
    }
}
