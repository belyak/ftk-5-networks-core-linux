#ifndef FDIOADAPTER_H_
#define FDIOADAPTER_H_

#include "IOAdapter.h"

class FDIOAdapter: public IOAdapter {
private:
	FILE * fd;
	int ifd;
public:
	FDIOAdapter();
	void setFD(FILE *fd);
	char readByte();
};

#endif /* FDIOADAPTER_H_ */
