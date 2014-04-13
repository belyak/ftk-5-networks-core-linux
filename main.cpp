#include <iostream>
#include "statistics.h"

int main() {
	PersistentStatistics ps;
	Statistics * s = new Statistics(ps);
	//std::wcout << L"TEST" << *s->LETTERS << std::endl;
//	char buffer[200];
//	std::cout << "Please enter string:";
//	std::cin >> buffer;
//	s->putLine(buffer);
//	s->dumpLines();
//	std::cout << "Please enter string:";
//	std::cin >> buffer;
//	s->putLine(buffer);
//	s->dumpLines();
//	cout << "Going to clear buffer" << std::endl;
	s->putLine("abc abc abc foo foo зая пп пп def a2 a2 a65");
	s->dumpLines();
	cout << "Going to calculate statistics..." << std::endl;
	s->calculate();
	cout << "OK" << std::endl;
	return 0;
}
