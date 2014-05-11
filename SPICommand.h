#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

#include "Encoder.h"

class SPICommand {

protected:
	CommandResponse* response;
	Statistics* statistics;
    Encoder * encoder;
	std::string current_line;
	std::string keyword;

    std::string get_rest();
    
public:
	virtual void set_statistics(Statistics& statistics);
    
    void set_encoder(Encoder * encoder);

	std::string get_keyword();
    
    void set_keyword(std::string);

	inline void prepare_response();

	virtual CommandResponse run();

	void set_current_line(std::string current_line);
};

class VersionCommand: public SPICommand {
public:
    CommandResponse run();
};

class ExitCommand: public SPICommand {
    CommandResponse run();
};

class PutLineCommand: public SPICommand {
    CommandResponse run();
};

class ClearBufferCommand: public SPICommand {
    CommandResponse run();
};

class CalcCommand: public SPICommand {
    CommandResponse run();
};

class PrintStatisticsCommand: public SPICommand {
    CommandResponse run();
};

class SaveCommand: public SPICommand {
    CommandResponse run();
};

class LoadCommand: public SPICommand {
    CommandResponse run();
};

typedef std::map<std::string, SPICommand*> RegisteredCommands;

RegisteredCommands init_registered_commands(Statistics &, Encoder &);

#endif
