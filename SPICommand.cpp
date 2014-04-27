#include <string>

#include "SPI.h"
#include "SPICommand.h"

#include "create_message.h"

std::string SPICommand::get_keyword() {
    static std::string keyword("ABCCommand");
    return keyword;
}

void SPICommand::set_result(const int code, const char * message) {
    this->result_code = code;
    this->result_txt = (char *)message;
}

void SPICommand::run() {}

void VersionCommand::run() { 
    this->set_result(200, SERVER_VERSION);
}

void ExitCommand::run() {
    this->set_result(200, "Good bye!");
}