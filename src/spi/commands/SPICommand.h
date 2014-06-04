#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

#include "../../encoder/Encoder.h"

/**
 * Базовый класс для всех команд, поддерживаемых сервером.
 */
class SPICommand {
protected:
    CommandResponse* response;
    Statistics* statistics;
    Encoder * encoder;
    SPI * spi;
    std::string current_line;
    std::string keyword;

    std::string get_rest();

public:
    void init(Statistics & statistics, Encoder * encoder, SPI * spi, std::string keyword);
    std::string get_keyword();
    inline void prepare_response();
    virtual CommandResponse * run();
    void set_current_line(std::string current_line);
};

class VersionCommand : public SPICommand {
public:
    CommandResponse * run();
};

class ExitCommand : public SPICommand {
    CommandResponse * run();
};

class PutLineCommand : public SPICommand {
    CommandResponse * run();
};

class PutTextCommand: public SPICommand {
    CommandResponse * run();
};

class ClearBufferCommand : public SPICommand {
    CommandResponse * run();
};

class CalcCommand : public SPICommand {
    CommandResponse * run();
};

class PrintStatisticsCommand : public SPICommand {
    CommandResponse * run();
};

class SaveCommand : public SPICommand {
    CommandResponse * run();
};

class LoadCommand : public SPICommand {
    CommandResponse * run();
};

class MergeCommand : public SPICommand {
    CommandResponse * run();
};

class SetEncodingCommand: public SPICommand {
    CommandResponse * run();
};

class SetTransferModeCommand: public SPICommand {
    CommandResponse * run();
};

// Хэш, хранящий соответствие мнемоника команды (строка) -> экземпляр объекта команды
typedef std::map<std::string, SPICommand*> RegisteredCommands;

/**
 * Метод, в котором происходит регистрация всех поддерживаемых сервером команд
 */
RegisteredCommands init_registered_commands(Statistics &, Encoder &, SPI *);

#endif
