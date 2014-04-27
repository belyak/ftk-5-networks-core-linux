#ifndef SPI_H
#define	SPI_H

#include "CommandResponse.h"

#include <string>

#define SERVER_BANNER "Text frequency analysis server v.%s ready."
#define SERVER_VERSION "0.02"

/*
 * Server Protocol Interpreter
 * базовый класс для интерпретатора взаимдействующего с сокетом и 
 * интерпретатора взаимодействующего со стандартным вводом/выводом
 */
class SPI {
protected:
    /**
     * отправляет клиенту сообщение
     * @param code код
     * @param data текст сообщения
     */
    virtual void send_message(const int code, const char * data) = 0;
        virtual void send_message(CommandResponse & response) = 0;
    /**
     * возвращает первое слово в строке, разделитель - пробел.
     */
    std::string first_word(std::string & line);
    /**
     * получает от клиента строку, заканчивающуюся разделителем CRLF
     * @return 
     */
    virtual char * read_line();
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
    virtual void start();

};

/***
 * Реализация SPI взаимодействующая с сокетом.
 */
class SocketSPI: public SPI {
private:
    int client_sfd; // socket file descriptor
protected:
    virtual void send_message(const int code, const char * data);
    virtual void send_message(CommandResponse & response);
    virtual unsigned char read_byte(bool & read_ok);
public:
    /**
     * конструктор
     * @param client_socket_fd открытый сокет входящего клиентского соединения
     */
    SocketSPI(int client_socket_fd);
    ~SocketSPI();
};

#endif	/* SPI_H */

