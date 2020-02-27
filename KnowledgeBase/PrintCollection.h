#pragma once
#ifndef _STDAFX_H
#define _STDAFX_H

#include <map>
#include <set>
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>

using std::map;
using std::set;
using std::pair;
using std::vector;
using std::string;

template<typename Collection, typename D> string Join(const Collection& c, const D& d) {
	std::stringstream ss;
	bool is_first = true;

	for (const auto& item : c) {
		if (!is_first) {
			ss << d;
		}
		is_first = false;
		ss << item;
	}
	return ss.str();
}

template<typename Fst, typename Sec>	std::ostream& operator<<(std::ostream& os, const pair<Fst, Sec>& p) {
	return os << p.first << " — " << p.second;
}
template<typename Key, typename Val>	std::ostream& operator<<(std::ostream& os, const map <Key, Val>& m) {
	return os << Join(m, '\n');
}

template<typename T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
	return os << Join(vec, '\n');
}
template<typename T> std::ostream& operator<<(std::ostream& os, const set<T>& set) {
	return os << Join(set, '\n');
}

#endif