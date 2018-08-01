#include <conio.h>
#include <stdio.h>
#include <time.h>

#include "Knowledge.h"
#include "Menu.h"

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

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	
	/*vector<string> agv;
	for (size_t i(0); i < argc; ++i) {
		agv.push_back(argv[i]);
	}*/

	const know data("data");
	
	char command = '\0';
	std::string cycle_str = "";
	size_t count = 0;
	know temp;

	do {
		system("cls");

		cycle_str = "";
		command = '\0';

		GeneralMenu();
		//std::cin.clear();
		command = (char)_getch();

		switch (command) {
		case '1': 
			std::cout << data << std::endl;
			_getch();
			break;
		case '2': 
			std::getline(std::cin, cycle_str);
			std::cout << data.FindDif(cycle_str) << std::endl;
			_getch();
			break;
		case '3':
			std::cout << "Enter count of terms: ";
			std::cin >> count;
			std::cout << data.GetSomeNotif(count);
			_getch();
			break;
		case '4':
			std::cout << "Enter filename: ";
			std::getline(std::cin, cycle_str);
			data.DumpToFile(cycle_str);
			_getch();
			break;
		case '5':
			std::cout << "Enter count of terms: ";
			std::cin >> count;

			temp = data.GetSomeNotif(count);

			std::cout << "Enter filename: ";
			std::cin >> cycle_str;

			temp.DumpToFile(cycle_str);
			std::cout << temp;
			_getch();
			break;
		case '6':
			command = 'q';
			_getch();
			break;
		default: 
			std::cerr << "Unknow command. Try again!\a"; 
			_getch();
			break;
		}
		
		std::cout << std::endl;
		system("pause");

	} while (command != 'q');

	return 0;
}