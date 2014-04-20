#ifndef _PERSISTENT_STATISTICS_H_
#define _PERSISTENT_STATISTICS_H_

#include <string>

#include "statistics.h"

#define MAX_LINE_LENGTH 2048

class PersistentStatistics {

public:
	StatisticsMap * data;
private:
	std::wstring * name;
	void setName(std::wstring name);
public:
	PersistentStatistics(std::wstring name, StatisticsMap & data);
	bool store(std::wstring name);
	bool load(std::wstring name);
	const char * get_filename();
};

#endif
