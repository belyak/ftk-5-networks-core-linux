#ifndef COMMANDRESPONSE_H
#define	COMMANDRESPONSE_H

#include <string>

class CommandResponse {
private:
    bool is_multi_line;
    int code;
    std::string line;
public:
    CommandResponse(const int code, const std::string line);
    CommandResponse(const int code, const std::string * lines, const int lines_count);
    char * raw();
};

#endif	/* COMMANDRESPONSE_H */

