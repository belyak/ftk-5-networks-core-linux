#include <iostream>
#include <locale>
#include <string>
#include <stdio.h>

#include "statistics.h"
#include "FDIOAdapter.h"

using std::cout;
using std::wcout;
using std::endl;


int main_stats() {
	std::locale::global(std::locale("ru_RU.UTF-8"));
	StatisticsMap sm;
	Statistics * s = new Statistics(L"current");
	s->putLine(L"abc abc abc foo foo зая пп пп def a2 a2 a65");
	s->dumpLines();
	cout << "Going to calculate statistics..." << std::endl;
	s->calculate();
	wcout << L"OK" << std::endl;
	s->save(std::wstring(L"some name"));
	wcout << L"statistics has been saved...";
	wcout << L"loading..." << std::endl;
	s->load(std::wstring(L"statistics.dat"));
	wcout << L"loaded" << std::endl;
	s->save(L"test");
	s->dumpLines();
	return 0;
}


int main() {
	std::cout << "CReating adapter..." << std::endl;
	FDIOAdapter * my_adapter = new FDIOAdapter();

	FILE * fd = fopen("test_incoming_data", "r");

	my_adapter->setFD(fd);

	while (!feof(fd)) {
		while (!feof(fd) and !my_adapter->hasLine()) {
			my_adapter->processByte();
		}
		std::cout << my_adapter->getLine() << " << was the line..." << std::endl;
	}
	fclose(fd);
	return 0;
}
