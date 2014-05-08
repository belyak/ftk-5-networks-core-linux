#include "Encoder.h"


bool Encoder::setEncoding(const char * encoding) {
     descr_out = iconv_open(encoding, "WCHAR_T");

    if ((iconv_t)-1 == descr_out) {
        return false;
    }

    descr_in = iconv_open("WCHAR_T", encoding);

    if ((iconv_t)-1 == descr_in) {
        return false;
    }
    return true; 
}

string Encoder::decode(wstring input_string) {

    const char * in_string = (char*)input_string.c_str();
    size_t in_string_length = (input_string.length() + 1)*sizeof (wchar_t );

    char * result = new char[2048];
    char * result_to_out = result;
    size_t result_len = 2048 * sizeof(char);

    size_t conversion_result = iconv(descr_out, (char **)&in_string, &in_string_length, (char**)&result, &result_len);

    s_result = string(result_to_out);

    delete [] result_to_out;

    return s_result;
}

wstring Encoder::encode(string input_string) {

    const char * in_string = input_string.c_str();
    size_t in_string_length = (input_string.length() + 1) * sizeof(char);

    wchar_t * result = new wchar_t[2048];
    wchar_t * result_to_out = result;
    size_t result_len = 2048 * sizeof (wchar_t);

    size_t conversion_result = iconv(descr_in, (char **)&in_string, &in_string_length, (char**)&result, &result_len);

    w_result = wstring(result_to_out);

    delete [] result_to_out;

    return w_result;
}