#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include "SPI.h"
#include "SPICommand.h"
#include "CommandResponse.h"

#include "create_message.h"
#include "lgs_constants.h"


void SPICommand::set_statistics(Statistics& statistics) {
    this->statistics = &statistics;
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
/*
CommandResponse PutLineCommand::run() {
    std::string rest(this->current_line.substr(this->get_keyword().length() + 1));
    std::cout << "REST:`" << rest << "`" << std::endl;
    
    int max_buffer_len = rest.length()*2;
    wchar_t * buffer = new wchar_t[max_buffer_len];
    mbstowcs(buffer, rest.c_str(), max_buffer_len);
    std::wstring line(buffer);
    delete buffer;
    
    this->statistics->putLine(line);
    int lCount = this->statistics->getLinesCount();
    char response_txt[MAX_LINE_LENGTH];
    sprintf(response_txt, "line has been collected (%d at the moment).", lCount);
    return * new CommandResponse(200, response_txt);
}

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

CommandResponse CalcCommand::run() {
    this->statistics->calculate();
    char buffer[MAX_LINE_LENGTH];
    int lCount = this->statistics->getLinesCount();
    int wCount = this->statistics->getWordsCount();
    sprintf(buffer, "Calculated (%d lines, %d words)", lCount, wCount);
    return * new CommandResponse(200, buffer);
}

inline void SPICommand::prepare_response() {
	// TODO - implement SPICommand::prepare_response
	throw "Not yet implemented";
}
*/