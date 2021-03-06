#include "Statistics.h"
#include "PersistentStatistics.h"

#include <list>
#include <iostream>
#include <string>
#include <fstream>

using std::wstring;
using std::wcout;
using std::endl;

// алфавит из которого могу состоять слова обрабатываемых текстов.
// на данный момент определен как спрочные и прописные символы латинского
// и русского алфавитов и арабские цифры.
const wstring * Statistics::LETTERS =
		new wstring(L"ABCEDFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфхцчшщьыъэюя1234567890");


Statistics::Statistics(wstring name) {
	words_count = 0;
	lines_count = 0;
	if (name.length() > 0) {
		this->name = wstring(name);
	} else {
		this->name = L"current";
	}
	this->storage = new PersistentStatistics(this->name, this->data);
}

void Statistics::putLine(wstring line) {
	wstring * s = new wstring(line);
	lines.push_back(*s);
	lines_count += 1;
}

void Statistics::clearBuffer() {
	this->lines.clear();
	this->data.clear();
        this->lines_count = 0;
        this->words_count = 0;
}

void Statistics::putWord(wstring word, unsigned int increment) {
	if (this->data.find(word) == this->data.end()) {
		this->data[word] = increment;
	} else {
		this->data[word] += increment;
	}
}

void Statistics::calculate() {

	for (StringList::iterator i = this->lines.begin(); i != this->lines.end(); i++) {
		wstring & line = *i;
		wstring::size_type word_start = 0;
		std::wstring::size_type pos = line.find_first_not_of(*this->LETTERS, 0);

		while (pos != wstring::npos) {
			const wstring word(line.substr(word_start, pos - word_start));
			putWord(word);
			word_start = line.find_first_of(*this->LETTERS, pos);
			pos = line.find_first_not_of(*this->LETTERS, word_start);
		}

		if (word_start != wstring::npos) {
			const wstring word(line.substr(word_start));
			putWord(word);
		}
	}
}

void Statistics::merge(Statistics & anotherStatistics) {
    StatisticsMap & anotherData = anotherStatistics.data;
    for (StatisticsMap::iterator i = anotherData.begin(); i != anotherData.end(); i++) {
        StatisticsEntry entry = *i;
        this->putWord(entry.first, entry.second);
    }
    return;
}

bool Statistics::load(std::wstring name) {
	bool loadResult = this->storage->load(name);
        if (loadResult) {
            this->data = * this->storage->data;
        }
	return loadResult;
}
