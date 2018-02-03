#pragma once
#pragma comment(lib, "C:/Users/Кирилл/Desktop/C++/Libs/CollectionOut/Debug/CollectionOut.lib")

#ifndef _KNOWLEDGE_H
#define _KNOWLEDGE_H

#include <algorithm>
#include <iterator>
#include <utility>
#include <fstream>
//#include <cctype>
#include <string>
#include <map>
#include <set>

#include "EXCEPT.h"
#include "C:/Users/Кирилл/Desktop/C++/Libs/CollectionOut/CollectionOut/stdafx.h"



namespace Program {
	class Knowledge {
	private:
		map<string, string> not_to_dif; // термин - определение
		
		friend vector<string> SplitIntoWords(const string&);
		friend bool is_contain(vector<string>, vector<string>);
	public:
		Knowledge() : not_to_dif() {};
		Knowledge(const string&);
		Knowledge(const Knowledge&);
		Knowledge& operator=(const Knowledge&);
		Knowledge& operator+=(const Knowledge&);

		inline size_t size() const {
			return not_to_dif.size();
		}

		int count(const string& dif) const {
			return count_if(begin(not_to_dif), end(not_to_dif), 
				[dif](const pair<string,string>& val) {
				return val.first == dif;
			});
		}

		vector<pair<string, string>> find_dif(const string&) const noexcept;

		map<string, string> unde_the_letter(char letter) const{
			if (std::count_if(begin(not_to_dif), end(not_to_dif),
				[letter](const pair<string,string>& val) {
				return val.first[0] == letter;
			}) < 1) {
				throw std::runtime_error(EXCEPT("Not found. May be wrong register"));
			}

			auto it = std::find_if(begin(not_to_dif), end(not_to_dif), 
				[letter](const pair<string, string>& val) {
				return val.first[0] == letter;
			});
			
			auto it_end = it;
			while (it_end->first[0] == letter) {
				it_end++;
			}
			return { it, it_end };
		}

		void AddTerm(const string& notiff, const string& diff) {
			if (notiff.empty() || diff.empty()) {
				throw std::invalid_argument(EXCEPT("Invalid notification of diffinition"));
			}
			not_to_dif.insert({ notiff, diff });
		}

		friend void GetOutTrash(const string&, const string&);
		friend bool operator==(const string&, const string&);
		friend std::ostream& operator<<(std::ostream& os, const Knowledge& value) {
			return os << value.not_to_dif;
		}
	};
}
#endif // !_KNOWLEDGE_H