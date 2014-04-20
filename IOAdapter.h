#ifndef IOADAPTER_H_
#define IOADAPTER_H_

#include <string>

#include "lgs_constants.h"

class IOAdapter {
private:
	std::string lastLine;
	bool hasCompleteLine;
	int writePosition;
	char chrbuf[MAX_LINE_LENGTH];
public:
	IOAdapter();
	virtual ~IOAdapter();

	virtual char readByte() { return 's'; }
	void processByte();
	bool hasLine();
	std::string getLine();

};

#endif /* IOADAPTER_H_ */
