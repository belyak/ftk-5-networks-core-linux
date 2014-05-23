#ifndef SOCKETSPI_H
#define	SOCKETSPI_H

#include "SPI.h"

/***
 * Реализация SPI взаимодействующая с сокетом.
 */

class SocketSPI : public SPI {
private:
    int client_sfd; // socket file descriptor
protected:
    virtual void send_message(const int code, wstring data);
    virtual void send_message(CommandResponse & response);
    virtual unsigned char read_byte(bool & read_ok);
public:
    /**
     * конструктор
     * @param client_socket_fd открытый сокет входящего клиентского соединения
     */
    SocketSPI(int client_socket_fd);
    virtual ~SocketSPI();
};

#endif
