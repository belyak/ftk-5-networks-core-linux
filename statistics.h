#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "persistent_statistics.h"

using std::wstring;
using std::map;
using std::list;
using std::cout;
using std::endl;

typedef list<wstring> StringList ;
typedef map<wstring, unsigned int> StatisticsMap;
typedef std::pair<wstring, unsigned int> StatisticsEntry;


class Statistics {

protected:

    int words_count;
    int lines_count;
    PersistentStatistics * storage;

    StringList lines;
    StatisticsMap data;

private:
    void putWord(wstring word);

public:
    static const wstring * LETTERS;

	Statistics(PersistentStatistics& storage);
	void putLine(wstring line);
    void clearBuffer();
    void calculate();
    bool load(const char * name);
    bool save(const char * name);
    int getLinesCount() { return lines_count; }
    int getWordsCount() { return words_count; }

    void dumpLines();
};

#endif
