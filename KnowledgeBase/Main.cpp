#include <conio.h>

#include "Knowledge.h"

template<typename Iter>
void Print(const Iter& begin, const Iter& end) {
	vector<Iter::value_type> range(begin, end);
	for (const auto& item : range) {
		std::cout << item << std::endl;
	}
}

void PrintFile(const string& filename) {
	std::ifstream fin(filename);

	while (!fin.eof()) {
		std::cout << char(fin.get());
	}
}

using namespace Program;

int main() {
	setlocale(LC_ALL, "Russian");

	Knowledge db3("first_and_second.txt", ifc::clr);
	std::cout << db3.GetSomeNotif(100, 3);
	
	//db3.DumpToFile();
	_getch();
	return 0;
}