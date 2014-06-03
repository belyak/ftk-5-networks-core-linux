#ifndef ABSTRACTCONVERTER_H
#define	ABSTRACTCONVERTER_H

#include <string>

/**
 * Абстрактный базовый класс конвертера.
 * Реализованный конвертер должен предоставлять методы кодировани и 
 * декодирования сообщений, а также длину чанка - т.е. есть количество байт, 
 * которым должна быть кратна длина закодированного сообщения для его 
 * нормального декодирования.
 */
class AbstractConverter {
public:
    virtual unsigned char get_chunk_size()=0;
    virtual std::string encode(const std::string & message)=0; 
    virtual std::string decode(const std::string & message)=0;
};

#endif	/* ABSTRACTCONVERTER_H */

