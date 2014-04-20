#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "lgs_types.h"

#include "statistics.h"
#include "persistent_statistics.h"

PersistentStatistics::PersistentStatistics(std::wstring name, StatisticsMap & data){
    this->name = new std::wstring(name);
    this->data = (StatisticsMap *)&data;
}

void PersistentStatistics::setName(std::wstring name) {
	delete this->name;
	this->name = new std::wstring(name);
}

const char * PersistentStatistics::get_filename(){
	std::string normal_string((char*)this->name->c_str());
	std::string filename_string = normal_string + std::string(".dat");
	return (const char *)filename_string.c_str();
}


bool PersistentStatistics::store(std::wstring name) {
	this->setName(name);
	const char * filename = this->get_filename();
	std::wcout << L"GOING TO WRITE TO " << filename << std::endl;
	std::wofstream output_file;
	output_file.open(this->get_filename(), std::ios::binary | std::ios::trunc);

	for (StatisticsMap::iterator i = this->data->begin(); i != this->data->end(); i++) {
		StatisticsEntry entry = *i;

		output_file << entry.first << L" " << entry.second << std::endl;
	}
	output_file.close();
	return true;
}

bool PersistentStatistics::load(std::wstring name) {
	this->setName(name);

	wchar_t buffer[MAX_LINE_LENGTH];


	std::wcout << L"before opening..." << std::endl;
	std::wifstream input_file;
	input_file.open(this->get_filename(), std::ios::in | std::ios::binary);
	while (input_file.eof() != true) {
		input_file.getline(buffer, MAX_LINE_LENGTH);
		std::wstring data(buffer);

		std::wstring::size_type space_pos = data.find(L" ");
		if (space_pos != std::wstring::npos) {
			std::wstring word(data.substr(0, space_pos));
			std::wstring count_str(data.substr(space_pos));
			int count = atoi((char*)count_str.c_str());
			(*this->data)[word] = count;
		}
	}
	input_file.close();
	return true;
}
