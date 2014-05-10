#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

class SPICommand {

protected:
	CommandResponse* response;
	Statistics* statistics;
	std::string current_line;
	std::string keyword;

public:
	virtual void set_statistics(Statistics& statistics);

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

typedef std::map<std::string, SPICommand*> RegisteredCommands;

RegisteredCommands init_registered_commands();

#endif
