#include <iostream>
#include "statistics.h"
#include <locale>

using std::cout;
using std::endl;


int main() {
	std::locale::global(std::locale("ru_RU.UTF-8"));
	PersistentStatistics ps;
	Statistics * s = new Statistics(ps);
	s->putLine(L"abc abc abc foo foo зая пп пп def a2 a2 a65");
	s->dumpLines();
	cout << "Going to calculate statistics..." << std::endl;
	s->calculate();
	cout << "OK" << std::endl;
	return 0;
}
