#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include "SPI.h"
#include "SPICommand.h"
#include "CommandResponse.h"

#include "create_message.h"
#include "lgs_constants.h"


void SPICommand::set_statistics(Statistics& statistics) {
    this->statistics = &statistics;
}

void SPICommand::set_encoder(Encoder* encoder) {
    this->encoder = encoder;
}

std::string SPICommand::get_keyword() {
    return keyword;
}

void SPICommand::set_keyword(std::string kw) {
    this->keyword = kw;
}

void SPICommand::set_current_line(std::string current_line) {
    this->current_line = std::string(current_line);
}

CommandResponse SPICommand::run() {
    return * new CommandResponse(200, L"Abstract response");  
}


CommandResponse VersionCommand::run() { 
    return * new CommandResponse(200, SERVER_VERSION);
}

CommandResponse ExitCommand::run() {
    return * new CommandResponse(200, L"Good bye!");
}

CommandResponse PutLineCommand::run() {
    std::string rest = this->current_line.replace(0, this->keyword.length() + 1, "");
    
    std::wstring line = this->encoder->encode(rest);
    
    std::cout << " going to putLine, len:" << line.length() << std::endl;
    this->statistics->putLine(line);
    int lCount = this->statistics->getLinesCount();
    std::wstringstream wss;
    wss << L"line has been collected (" << lCount << L" at the moment).";
    return * new CommandResponse(200, wss.str());
}

CommandResponse CalcCommand::run() {
    this->statistics->calculate();
    std::wstringstream wss;
    int lCount = this->statistics->getLinesCount();
    int wCount = this->statistics->getWordsCount();
    wss << L"Calculated (" << lCount << L" lines, " << wCount << L" words)";
    return * new CommandResponse(200, wss.str());
}

/*
CommandResponse SaveCommand::run() {
    std::string rest(this->current_line.substr(this->get_keyword().length() + 1));
    std::cout << "REST:`" << rest << "`" << std::endl;
    
    int max_buffer_len = rest.length()*2;
    wchar_t * buffer = new wchar_t[max_buffer_len];
    mbstowcs(buffer, rest.c_str(), max_buffer_len);
    std::wstring name(buffer);
    delete buffer;
    
    this->statistics->save(name);
    char msg[MAX_LINE_LENGTH];
    sprintf(msg, "Statistics \"%s\" has been saved", rest.c_str());
    return * new CommandResponse(200, msg);
}

inline void SPICommand::prepare_response() {
	// TODO - implement SPICommand::prepare_response
	throw "Not yet implemented";
}
*/

RegisteredCommands init_registered_commands(Statistics & statistics, Encoder & encoder) {
    
    static RegisteredCommands registered_commands;
    
    #define REGISTER_CMD(CMD_CLS, CMD_KW) { SPICommand * cmd = new CMD_CLS(); \
    cmd->set_statistics(statistics); \
    cmd->set_keyword(#CMD_KW); \
    cmd->set_encoder(&encoder); \
    registered_commands[cmd->get_keyword()] = cmd; }
    
    REGISTER_CMD(VersionCommand, ver);
    REGISTER_CMD(ExitCommand, exit);
    REGISTER_CMD(PutLineCommand, pl);
    REGISTER_CMD(CalcCommand, calc);
    
    return registered_commands;
}