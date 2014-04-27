#ifndef SPICOMMAND_H
#define	SPICOMMAND_H

#include <string>

// укороченнное определение метода, возвращающего текст команды:
#define COMMAND_KEYWORD(K) virtual std::string get_keyword() { static std::string t(K); return t; }


class SPICommand {
protected:
    int client_sfd;
    CommandResponse * response;
public:
    virtual std::string get_keyword();
    inline void prepare_response();
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

