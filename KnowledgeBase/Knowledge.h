#pragma once

#ifndef _KNOWLEDGE_H
#define _KNOWLEDGE_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <map>
#include <set>

#include "PrintCollection.h"
#include "EXCEPT.h"
#include <time.h>

using std::map;
using std::set;
using std::pair;
using std::list;
using std::string;
using std::vector;

namespace Program {
	int GetUniqueNumber(size_t);
	
	class Knowledge {
	private:
		map<string, string> not_to_dif; // термин - определение
		
		friend vector<string> SplitIntoWords(const string&);
		friend bool is_contain(vector<string>, vector<string>);
		friend std::string GetOutStrTrash(std::string);
	public:
		Knowledge() : not_to_dif() {};
		Knowledge(const string&, bool is_clear=false);
		Knowledge(const Knowledge&);
		~Knowledge();

		Knowledge& operator=(const Knowledge&);
		Knowledge& operator+=(const Knowledge&);

		pair<string, string> operator[](size_t index) const{
			if (index > not_to_dif.size()) {
				throw std::out_of_range(EXCEPT("Index more than range size"));
			}

			size_t i = 0;
			for (const auto& item : not_to_dif) {
				if (i == index) {
					return item;
				}
				++i;
			}
		}

		inline size_t size() const {
			return not_to_dif.size();
		}

		auto _begin() const{
			return not_to_dif.begin();
		}
		auto _end() const {
			return not_to_dif.end();
		}

		int count(const string& dif) const {
			return count_if(begin(not_to_dif), end(not_to_dif), 
				[dif](const pair<string,string>& val) {
				return val.first == dif;
			});
		}


		map<string, string> find_dif(const string&) const noexcept;

		map<string, string> unde_the_letter(char) const;

		map<string, string> GetSomeNotif(size_t, const set<char>&) const;
		map<string, string> GetSomeNotif(size_t) const;

		void Add(const pair<string, string>& val) {
			if (val.first.empty() || val.second.empty()) {
				throw std::invalid_argument(EXCEPT("Invalid notification of diffinition"));
			}
			not_to_dif.insert(val);
		}

		friend void GetOutTrash(const string&, const string&);
		friend bool operator==(const string&, const string&);
		friend std::ostream& operator<<(std::ostream& os, const Knowledge& value) {
			return os << value.not_to_dif;
		}
	};
}
#endif // !_KNOWLEDGE_H