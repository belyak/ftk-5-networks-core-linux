#include "CommandResponse.h"
#include "lgs_constants.h"

#include <stdio.h>

CommandResponse::CommandResponse(const int code, const std::string line) {
    this->code = code;
    this->line = line;
    this->is_multi_line = false;
}

CommandResponse::CommandResponse(const int code, const std::string * lines, const int lines_count) {
    //TODO: add realization
}

char * CommandResponse::raw() {
    static char buffer[MAX_LINE_LENGTH*100];
    sprintf(buffer, "%d %s\r\n", this->code, this->line.c_str());
    return buffer;
}
