#ifndef PLAINCONVERTER_H
#define	PLAINCONVERTER_H

#include "AbstractConverter.h"

/**
 * Конвертер не изменяющий сообщения при кодировании/декодировании
 */
class PlainConverter: public AbstractConverter {
public:
    virtual unsigned char get_chunk_size() { return 1; }
    virtual std::string encode(const std::string & message);
    virtual std::string decode(const std::string & message);
};

#endif	/* PLAINCONVERTER_H */

