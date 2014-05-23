#include "create_message.h"

#include "../lgs_constants.h"

#include <string.h>
#include <stdio.h>

char * create_message(const int code, const char * msg) {
    static char buff[MAX_LINE_LENGTH];
    memset(buff, 0, sizeof(buff));
    sprintf(buff, "%d %s%s", code, msg, CRLF);
    return buff;
}