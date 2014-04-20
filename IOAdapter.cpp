/*
 * IOAdapter.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: andy
 */

#include "IOAdapter.h"

#include <iostream>
#include <string>
#include <string.h>


IOAdapter::IOAdapter() {
	// TODO Auto-generated constructor stub
	this->hasCompleteLine = false;
	this->writePosition = 0;
}

bool IOAdapter::hasLine() {
	return this->hasCompleteLine;
}

std::string IOAdapter::getLine() {
	this->hasCompleteLine = false;
	return this->lastLine;
}

void IOAdapter::processByte() {
	unsigned int separator_len = strlen(LINES_SEPARATOR);
	char in_byte;
	try {
		in_byte = this->readByte();
	} catch (char * msg){
		std::cerr << "Got exception: " << msg << std::endl;
		return;
	}
	this->chrbuf[this->writePosition] = in_byte;
	this->writePosition++;

	std::cout << this->writePosition << "  " << this->chrbuf << strlen(this->chrbuf) << std::endl;

	if (this->writePosition > separator_len) {
		if (0 == strncmp(this->chrbuf + this->writePosition - separator_len, LINES_SEPARATOR, separator_len)) {
			this->hasCompleteLine = true;
			// удалим перенос строки
			this->chrbuf[writePosition - 2] = 0;
			this->chrbuf[writePosition - 1] = 0;

			this->lastLine = std::string(this->chrbuf);

			this->writePosition = 0;
		}
	}
}

IOAdapter::~IOAdapter() {
	// TODO Auto-generated destructor stub
}

