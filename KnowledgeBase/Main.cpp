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
using know = Knowledge;

int main() {
	setlocale(LC_ALL, "Russian");

	//know latin("C:\\Users\\Кирилл\\Desktop\\latin.txt");
	//latin.DumpToFile("C:\\Users\\Кирилл\\Desktop\\dmp.lat.txt");

	/*std::ofstream fout("diff_for_day.txt");
	know db1("1_and_2.txt");

	fout << db1.GetSomeNotif(25);*/

	//db1.DumpToFile("1_and_2.txt");
	_getch();
	return 0;
}