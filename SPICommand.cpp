#include <string>

#include <stdio.h>

#include "SPI.h"
#include "SPICommand.h"
#include "CommandResponse.h"

#include "create_message.h"
#include "lgs_constants.h"


std::string SPICommand::get_keyword() {
    static std::string keyword("ABCCommand");
    return keyword;
}

void SPICommand::prepare_response() {
    if (this->response != NULL) {
            delete response;
    }
}

#define RETURN_RESPONSE(r) {this->prepare_response(); this->response = r; return *this->response; }

CommandResponse SPICommand::run() {
    RETURN_RESPONSE( new CommandResponse(200, "Abstract response") );  
}

CommandResponse VersionCommand::run() { 
    RETURN_RESPONSE( new CommandResponse(200, SERVER_VERSION) );
}

CommandResponse ExitCommand::run() {
    RETURN_RESPONSE( new CommandResponse(200, "Good bye!") );
}