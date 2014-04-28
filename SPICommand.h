#ifndef SPICOMMAND_H
#define	SPICOMMAND_H

#include <string>

#include "statistics.h"

// укороченнное определение метода, возвращающего текст команды:
#define COMMAND_KEYWORD(K) virtual std::string get_keyword() { static std::string t(K); return t; }


class SPICommand {
protected:
    int client_sfd;
    CommandResponse * response;
    Statistics * statistics;
    std::string current_line; 
public:
    virtual void set_statistics(Statistics & statistics);
    void set_current_line(std::string current_line);
    virtual std::string get_keyword();
    inline void prepare_response();
    virtual CommandResponse run();
};

class PutLineCommand: public SPICommand {
public:
    COMMAND_KEYWORD("pl")
    virtual CommandResponse run();
};

class CalcCommand: public SPICommand {
public:
    COMMAND_KEYWORD("calc")
    virtual CommandResponse run();
};

class SaveCommand: public SPICommand {
public:
    COMMAND_KEYWORD("st")
    virtual CommandResponse run();
};

class VersionCommand: public SPICommand {
public:
    COMMAND_KEYWORD("ver")
    virtual CommandResponse run();
};

class ExitCommand: public SPICommand {
public:
    COMMAND_KEYWORD("exit")
    virtual CommandResponse run();
};

#endif	/* SPICOMMAND_H */

