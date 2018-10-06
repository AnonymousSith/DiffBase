#pragma once

#ifndef _KNOWLEDGE_H
#define _KNOWLEDGE_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <utility>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include <set>

#include "PrintCollection.h"
#include "EXCEPT.h"
#include <time.h>

using std::map;
using std::set;
using std::pair;
using std::string;
using std::vector;

namespace Program {
	enum class is_file_clear { clr = true, drt = false }; // have a file trash or not
	using ifc = is_file_clear;

	class Knowledge {
	private:
		map<string, string> term_to_dif; // term - diffinition
		
		mutable map<string, string> UsedWords; // already learned words

		void FillRememberDiffFromFile() const; // Fill in the repository of already learned words
		pair<string, string> DivideStr(const string&) const; // divides a string into a pair<term, diffinition>
		
		friend string GetOutFileType(string); // removes type of a file from the string
		friend vector<string> SplitIntoWords(const string&); // divides a string into vector<words>
		friend bool is_contain(vector<string>, vector<string>); // finds word intersections
	public:
		Knowledge() {};
		Knowledge(const Knowledge&);
		Knowledge(const map<string, string>&);
		Knowledge(const string&, ifc is_clear=ifc::drt);
		Knowledge& operator=(const Knowledge&);

		Knowledge operator+(const Knowledge&) const noexcept; // unite a KnowBases
		Knowledge& operator+=(const Knowledge&);

		pair<string, string> operator[](size_t) const; // beginning 0

		size_t size() const {
			return term_to_dif.size();
		}

		auto _begin() const{
			return term_to_dif.begin();
		}
		auto _end() const {
			return term_to_dif.end();
		}

		int count(const string&) const;

		map<string, string> FindDif(const string&)	const;	// returns similar words
		map<string, string> UndeTheLetter(char)		const;	// find all words unde the letter
		map<string, string> GetSomeNotif(size_t)	const;	// returns N terms

		void DumpRemember2File() const;
		void DumpToFile(string FileName="") const noexcept;

		void DiffForDay(const string& FileName) const;

		void Add(const pair<string, string>&);
		void Remove(const string&);

		friend void GetOutTrash(const string&, const string&);
		friend bool operator==(const string&, const string&);
		friend std::ostream& operator<<(std::ostream& os, const Knowledge& value) {
			return os << value.term_to_dif;
		}
	};
}
#endif // !_KNOWLEDGE_H