//#pragma comment(lib, "C:/Users/ ирилл/Desktop/C++/Libs/CollectionOut/Debug/CollectionOut.lib")

//#include "C:/Users/ ирилл/Desktop/C++/Libs/CollectionOut/CollectionOut/stdafx.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <conio.h>

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::string;

std::string GetFilename(std::string file) {
	std::reverse(begin(file), end(file));
	auto iter = file.begin();
	std::string ret = "";
	while (*iter != '\\') {
		ret.insert(begin(ret), *iter);
		iter++;
	}
	return ret;
}

#define EXCEPT(X) (X) + ((std::string("\a\nFile: ") + GetFilename(__FILE__) + "\nFunc: " + __func__ + "()" + "\nLine: " + std::to_string(__LINE__)))

template<typename Collection, typename D> string Join(const Collection& c, const D& d) {
	std::stringstream ss;
	bool is_fisrt = true;

	for (const auto& item : c) {
		if (!is_fisrt) {
			ss << d;
		}
		is_fisrt = false;
		ss << item;
	}
	return ss.str();
}

template<typename First, typename Second> std::ostream& operator<<(std::ostream& os, const pair<First, Second>& val) {
	return os << "(" << val.first << ";" << val.second << ")";
}
template<typename T> std::ostream& operator<<(std::ostream& os, const set<T>& set) {
	return os << Join(set, '\n');
}


class Knowledge {
private:
	map<string, string> not_to_dif; // Pair термин - определение
public:
	using iter = map<string, string>::iterator;

	Knowledge() : not_to_dif() {};
	Knowledge(iter begin, iter end) : not_to_dif(begin, end) {};
	Knowledge(const string& filename) {
		if (filename.empty()) {
			throw std::invalid_argument(EXCEPT("Empty filename!"));
		}
		std::ifstream fin(filename);

		if (!fin.is_open()) {
			throw std::runtime_error(EXCEPT("File is not open!"));
		}

		string temp_notion;

		if (fin) {
			while (!fin.eof()) {
				std::getline(fin, temp_notion);
				if (count(begin(temp_notion), end(temp_notion), 'Ч') < 1) {
					continue;
				}
				auto it = find(begin(temp_notion), end(temp_notion), 'Ч');

				not_to_dif.insert({ {begin(temp_notion), it},{it,end(temp_notion)} });
				
				//temp_notion.clear();
				//temp_diff.clear();
			}
		}
	}
	Knowledge(const vector<string>& range) {
		if (range.empty()) {
			return;
		}

	}

	string find_dif(const string& dif) const noexcept{
		for (const auto& item : not_to_dif) {
			if (item.first == dif) {
				return item.second;
			}
		}
		return "-1";
	}


	friend std::ostream& operator<<(std::ostream& os, const Knowledge& value) {
		for (const auto& item : value.not_to_dif) {
			os << item << std::endl;
		}
		return os;
	}
};


template<typename Iter>
void Print(const Iter& begin, const Iter& end) {
	vector<Iter::value_type> range(begin, end);
	for (const auto& item : range) {
		std::cout << item << std::endl;
	}
}


void GetOutRabish(const string& in, const string& out){
	if (in.empty()) {
		throw std::invalid_argument(EXCEPT("Wrong filename"));
	}

	std::ifstream fin(in);

	if (!fin.is_open() || fin.eof()) {
		throw std::runtime_error(EXCEPT("File is not open"));
	}
	set<string> mediator;
	string temp;

	string::iterator cyle_iter;
	bool is_begin_cat = false;
	if (fin) {
		while (!fin.eof()) {
			std::getline(fin, temp);

			cyle_iter = remove_if(begin(temp), end(temp), [](const char& sym) {
				return sym == '\t' || sym == '\n';
			});
			temp.erase(cyle_iter, end(temp));

			mediator.insert(temp);
		}
	}
	fin.close();

	mediator.erase("");

	std::ofstream fout(out);
	fout << mediator;
}

void PrintFile(const string& filename) {
	std::ifstream fin(filename);

	while (!fin.eof()) {
		std::cout << char(fin.get());
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	
	
	//GetOutRabish("a.txt", "out.txt");
	
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
	Knowledge base("out.txt");
	std::cout << base;
	_getch();
	return 0;
}