#ifndef COMMANDRESPONSE_H
#define	COMMANDRESPONSE_H

#include <string>

class CommandResponse {
private:
    bool is_multi_line;
    int code;
    std::wstring line;
    const std::wstring * lines;
    unsigned int lines_count;
    wchar_t * raw_response;
public:
    CommandResponse(const int code, const std::wstring line);
    CommandResponse(const int code, const std::wstring * lines, const unsigned int lines_count);
    virtual ~CommandResponse();
    wchar_t * raw();
};

#endif
