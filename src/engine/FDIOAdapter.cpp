#include "FDIOAdapter.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

FDIOAdapter::FDIOAdapter() {
	this->fd = NULL;
	this->ifd = 0;
}

char FDIOAdapter::readByte() {
		char buf[1] = {0};
		size_t m = read(this->ifd, buf, 1);
		if (m == 1) {
			return buf[0];
		} else {
			char * msg = new char[4];
			strcpy(msg, "EOF");
			throw msg;
		}
}

void FDIOAdapter::setFD(FILE * fd) {
	this->fd = fd;
	this->ifd = fileno(fd);
}
