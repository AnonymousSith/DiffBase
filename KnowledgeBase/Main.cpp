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

int main() {
	setlocale(LC_ALL, "Russian");

	Program::Knowledge bd("db1.txt",true);
	for (int i(0); i < 10000; ++i) {
		try {
			if (bd.GetSomeNotif(15).size() != 150) {
				std::cout << bd.GetSomeNotif(150).size() << std::endl;
			}
		}
		catch (const std::exception& ex) {
			std::cout << ex.what();
		}
	}

	/*Program::Knowledge tom1("tom1.txt");
	std::cout << tom1.size() << std::endl;

	Program::Knowledge tom2("tom2.txt");
	std::cout << tom2.size() << std::endl;
	
	Program::Knowledge tom3;
	tom3 += tom1;
	tom3 += tom2;

	std::cout << tom3 << std::endl;
	std::cout << tom3.size();*/
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