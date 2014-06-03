#include "create_message.h"

#include "../lgs_constants.h"

#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>

char * create_message(const int code, const char * msg) {
    static char buff[MAX_LINE_LENGTH];
    memset(buff, 0, sizeof(buff));
    
    std::stringstream sb;
    sb << code << " " << msg << CRLF;
    strcpy(buff, sb.str().c_str());
    return buff;
}