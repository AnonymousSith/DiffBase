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

	//std::cout << bd[103];

	/*double begin = clock();
	for (int i(0); i < 10; i++) {
		std::cout << bd.GetSomeNotif(100).size() << "; ";
	}
	double end = clock();
	std::cout << "Time: " << (end - begin) / CLOCKS_PER_SEC;*/
	_getch();
	return 0;
}