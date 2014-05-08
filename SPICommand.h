#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

class SPICommand {

protected:
	CommandResponse* response;
	Statistics* statistics;
	std::string current_line;
	const std::string keyword;

public:
	virtual void set_statistics(Statistics& statistics);

	virtual std::string get_keyword();

	inline void prepare_response();

	virtual CommandResponse run();

	void set_current_line(std::string current_line);
};

#endif
