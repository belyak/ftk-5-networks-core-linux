#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include "../lgs_types.h"
#include "PersistentStatistics.h"

using std::wstring;

/**
 * Класс реализующий основную логику работы сервера с текстами.
 */
class Statistics {

    friend class PrintStatisticsCommand;
    
protected:
    wstring name;
    int words_count;
    int lines_count;
    PersistentStatistics * storage;

    StringList lines;
    StatisticsMap data;

private:
    void putWord(wstring word, unsigned int increment = 1);

public:
    static const wstring * LETTERS;

    Statistics(wstring name = L"current");

    void putLine(wstring line);
    void clearBuffer();
    void calculate();
    int getLinesCount() { return lines_count; }
    int getWordsCount() { return words_count; }

    void merge(Statistics &);

    /* методы включенного объекта-хранилища: */
    void inline save(std::wstring name) { storage->store(name); }
    bool load(std::wstring name);
};

#endif
