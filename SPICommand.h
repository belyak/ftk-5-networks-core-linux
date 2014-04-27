#ifndef SPICOMMAND_H
#define	SPICOMMAND_H

#include <string>
// укороченнное определение метода, возвращающего текст команды:
#define COMMAND_KEYWORD(K) virtual std::string get_keyword() { static std::string t(K); return t; }

class SPICommand {
protected:
    int client_sfd;
    void set_result(const int code, const char * message);
public:    
    char * result_txt;
    int result_code;
public:
    virtual std::string get_keyword();
    virtual void run();
    
private:

};

class VersionCommand: public SPICommand {
public:
    COMMAND_KEYWORD("ver")
    virtual void run();
};

class ExitCommand: public SPICommand {
public:
    COMMAND_KEYWORD("exit")
    virtual void run();
};

#endif	/* SPICOMMAND_H */

