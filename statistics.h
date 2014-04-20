#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include "lgs_types.h"
#include "statistics.h"
#include "persistent_statistics.h"

using std::wstring;


class Statistics {

protected:
	wstring name;
    int words_count;
    int lines_count;
    PersistentStatistics * storage;

    StringList lines;
    StatisticsMap data;

private:
    void putWord(wstring word);

public:
    static const wstring * LETTERS;

    Statistics(wstring name);

    void putLine(wstring line);
    void clearBuffer();
    void calculate();
    int getLinesCount() { return lines_count; }
    int getWordsCount() { return words_count; }

    void dumpLines();

    /* методы включенного объекта-хранилища: */
    void inline save(std::wstring name) { storage->store(name); }
    bool load(std::wstring name);
};

#endif
