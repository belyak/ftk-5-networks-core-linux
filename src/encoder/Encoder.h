#ifndef ENCODER_H
#define	ENCODER_H

#include <iconv.h>
#include <string>

using std::string;
using std::wstring;

/**
 * Класс-обертка для работы с библиотекой iconv
 * предоставляет метод выставления клиентской кодировки и осуществляет 
 * двустороннее преобразование между клиентской кодировкой и способом
 * хранения символов в контейнере std::wstring.
 */
class Encoder {
private:
    wstring w_result;
    string s_result;
    iconv_t descr_in, descr_out;
public:
    bool setEncoding(const char * encoding = "UTF-8");
    string decode(wstring input_string);
    wstring encode(const string & input_string);
};

#endif	/* ENCODER_H */
