#include <conio.h>

#include "Knowledge.h"

using std::set;
using std::map;
using std::vector;
using std::string;

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

int main() {
	setlocale(LC_ALL, "Russian");
	Program::Knowledge data("FullText.txt");
	try {
		std::cout << data.find_dif("Альтруим");
	}
	catch (const std::exception& exc) {
		std::cout << exc.what();
	}
	//GetOutRabish("a.txt", "out.txt");
	//PrintFile("out.txt");
	//vector<string> str;

	//std::ifstream fin("text.txt");
	//if (!fin.is_open()) {
	//	std::cerr << "File is not open!\a";
	//	_getch();
	//}

	//string temp = "";
	//char symbol = '1';
	//if (fin) {
	//	while (!fin.eof()) {
	//		while (fin.get() != '.') {
	//			fin >> symbol;
	//			temp += symbol;
	//		}
	//		str.push_back(temp);
	//		//temp.clear();
	//	}
	//}
	//Print(begin(str), end(str));
	//std::cout << Program::SplitIntoWords("String compare");

	_getch();
	return 0;
}