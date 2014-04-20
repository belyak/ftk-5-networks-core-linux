#include <iostream>
#include <locale>
#include <string>

#include "statistics.h"

using std::cout;
using std::wcout;
using std::endl;


int main() {
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
	s->save(L"test.dat");
	s->dumpLines();
	return 0;
}
