#ifndef COMMANDRESPONSE_H
#define	COMMANDRESPONSE_H

#include <string>

/**
 * Класс для создания ответа сервера на основе числового кода ответа и
 * либо одной, либо нескольких строк текста.
 */
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
    /**
     * Метод для преобразования ответа в строку.
     */
    wchar_t * raw();
};

#endif
