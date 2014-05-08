#include "Statistics.h"
#include "PersistentStatistics.h"

#include <list>
#include <iostream>
#include <string>
#include <fstream>

using std::wstring;
using std::wcout;
using std::endl;

const wstring * Statistics::LETTERS =
		new wstring(L"ABCEDFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфхцчшщьыъэюя");


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
}

void Statistics::putWord(wstring word) {
	if (this->data.find(word) == this->data.end()) {
		this->data[word] = 1;
	} else {
		this->data[word]++;
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

	wcout << L"STATISTICS:" << endl;
	for (StatisticsMap::iterator i = this->data.begin(); i != this->data.end(); i++) {
		StatisticsEntry entry = *i;
		wcout << entry.first << L": " << entry.second << endl;
	}
}

void Statistics::dumpLines() {
	wcout << L"Current lines dump:" << endl;
	for (StringList::iterator i = lines.begin(); i != lines.end(); i++) {
		wcout << *i << endl;
	}
}

bool Statistics::load(std::wstring name) {
	bool loadResult = this->storage->load(name);
	return loadResult;
}
