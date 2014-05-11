#include "CommandResponse.h"
#include "lgs_constants.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>

CommandResponse::CommandResponse(const int code, const std::wstring line) {
    this->code = code;
    this->line = line;
    this->is_multi_line = false;
    this->lines = NULL;
    this->lines_count = 0;
}

CommandResponse::CommandResponse(const int code, const std::wstring * lines, const unsigned int lines_count) {
    this->code = code;
    this->lines = lines;
    this->lines_count = lines_count;
}

CommandResponse::~CommandResponse() {
    if (this->raw_response != NULL) {
        delete this->raw_response;
    }
    if (this->lines != NULL) {
        delete [] this->lines;
    }
}

wchar_t * CommandResponse::raw() {
    std::wstringstream response;
    if (this->is_multi_line) {
        // первая строка начинается с кода и пробела:
        response << this->code << ' ' << lines[0] << CRLF;
        // все строки идут без изменений: 
        for (int i = 1; i < lines_count - 1; i++) {
            response << lines[i] << CRLF;
        }
        // последняя строка начинается с кода и минуса
        response << this->code << '-' << lines[lines_count - 1] << CRLF;
    } else {
        response << this->code << ' ' << this->line << CRLF;
    }
    
    this->raw_response = new wchar_t[response.str().length() + 1];
    this->raw_response[response.str().length()] = L'\0';
    memcpy((void*)this->raw_response, (void*) response.str().data(), response.str().length()*sizeof(wchar_t));
    return this->raw_response;
}
