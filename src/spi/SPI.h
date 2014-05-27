#ifndef SPI_H
#define	SPI_H

#include "../encoder/Encoder.h"
#include "../engine/Statistics.h"
#include "commands/CommandResponse.h"
#include "../converters/AbstractConverter.h"

#include <string>

/**
 * Реализует логику взаимодействия с клиентом, не зависящую от типа ввода/вывода.
 * 
 * Два унаследованных класса - две реализации:
 * SocketSPI - ввод/вывод в дескриптор сокета
 * ConsoleSPI - ввод/вывод на стандартные ввод/вывод
 *  
 */
class SPI {
protected:
    Encoder encoder;
    AbstractConverter * converter;
    Statistics statistics;
    /**
     * отправляет клиенту сообщение
     * @param code код
     * @param data текст сообщения
     */
    virtual void send_message(const int code, std::wstring data) = 0;
    virtual void send_message(CommandResponse & response) = 0;
    /**
     * возвращает первое слово в строке, разделитель - пробел.
     */
    std::string first_word(std::string & line);

    /**
     * получает от клиента один байт
     * @param read_ok статус вызова
     * @return прочитанный байт
     */
    virtual unsigned char read_byte(bool & read_ok) = 0;
public:
    SPI();
    virtual ~SPI();
    /**
     * запуск интерпретатора
     */
    void start();
    
    /**
     * получает от клиента строку, заканчивающуюся разделителем CRLF
     * @return 
     */
    virtual char * read_line();
};

#endif
