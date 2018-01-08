#pragma once
#pragma comment(lib, "C:/Users/Кирилл/Desktop/C++/Libs/CollectionOut/Debug/CollectionOut.lib")

#ifndef _KNOWLEDGE_H
#define _KNOWLEDGE_H

#include <algorithm>
#include <iterator>
#include <utility>
#include <fstream>
#include <cctype>
#include <string>
#include <map>
#include <set>

#include "EXCEPT.h"
#include "C:/Users/Кирилл/Desktop/C++/Libs/CollectionOut/CollectionOut/stdafx.h"



namespace Program {
	void GetOutRabish(const string&, const string&);
	vector<string> SplitIntoWords(const string&);
	bool is_contain(vector<string>, vector<string>);
	bool operator==(const string&, const string&);

	class Knowledge {
	private:
		map<string, string> not_to_dif; // Pair термин - определение
		

	public:
		using _MyIt = map<string, string>::iterator;
		
		Knowledge() : not_to_dif() {};
		Knowledge(const string&);
		
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

		friend std::ostream& operator<<(std::ostream& os, const Knowledge& value) {
			return os << value.not_to_dif;
		}
	};
}
#endif // !_KNOWLEDGE_H