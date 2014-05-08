#ifndef CONSOLE_SPI_H
#define CONSOLE_SPI_H

#include "SPI.h"
#include "CommandResponse.h"

#include <string>

class ConsoleSPI : public SPI {


protected:
	/**
	 * отправляет клиенту сообщение
	 * @param code код
	 * @param data текст сообщения
	 */
	void send_message(const int code, std::wstring);

	void send_message(CommandResponse& response);

	/**
	 * получает от клиента один байт
	 * @param read_ok статус вызова
	 * @return прочитанный байт
	 */
	unsigned char read_byte(bool& read_ok);

public:
	ConsoleSPI();
};

#endif
