#include <conio.h>
#include <stdio.h>
#include <time.h>

#include "PrintCollection.h"
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

	//const know data("data");
	const know verbs("verbs");
	const know noun("noun");
	const know adj("adj");
	const know adverbs("adverbs");
	const know discourse("discourse");
	const know learn_now("learn_now");

	char command = '\0';
	std::string cycle_str = "";
	size_t count = 0;
	know temp;

	do{
		MENU::LearnEnglish();
		command = char(_getch());

		switch (command) {
		case '1':
			Topics();
			command = char(_getch());
			switch (command) {
			case '1':
				temp = noun;
				break;
			case '2':
				temp = adj;
				break;
			case '3':
				temp = verbs;
				break;
			case '4':
				temp = adverbs;
				break;
			case '5':
				temp = discourse;
				break;
			case '6':
				temp = learn_now;
				break;
			}
			temp.shuffle();

			
			break;
		case '2':
			break;
		}

		system("cls");
	} while (command != '2');


	//do {
	//	system("cls");

	//	cycle_str = "";
	//	command = '\0';

	//	GeneralMenu();
	//	//std::cin.clear();
	//	command = (char)_getch();

	//	switch (command) {
	//	case '1': 
	//		std::cout << data << std::endl;
	//		_getch();
	//		break;
	//	case '2': 
	//		std::getline(std::cin, cycle_str);
	//		std::cout << data.FindDif(cycle_str) << std::endl;
	//		_getch();
	//		break;
	//	case '3':
	//		std::cout << "Enter count of terms: ";
	//		std::cin >> count;
	//		std::cout << data.GetSomeNotif(count);
	//		_getch();
	//		break;
	//	case '4':
	//		std::cout << "Enter filename: ";
	//		std::getline(std::cin, cycle_str);
	//		data.DumpToFile(cycle_str);
	//		_getch();
	//		break;
	//	case '5':
	//		std::cout << "Enter count of terms: ";
	//		std::cin >> count;

	//		temp = data.GetSomeNotif(count);

	//		std::cout << "Enter filename: ";
	//		std::cin >> cycle_str;

	//		temp.DumpToFile(cycle_str);
	//		std::cout << temp;
	//		_getch();
	//		break;
	//	case '6':
	//		command = 'q';
	//		_getch();
	//		break;
	//	default: 
	//		std::cerr << "Unknow command. Try again!\a"; 
	//		_getch();
	//		break;
	//	}
	//	
	//	std::cout << std::endl;
	//	system("pause");

	//} while (command != 'q');

	return 0;
}