#include "Knowledge.h"
	
namespace Program {
	std::string GetOutStrTrash(std::string str) {
		auto it = std::find(begin(str), end(str), '.');
		str.erase(it, end(str));
		return str;
	}
	void GetOutTrash(const string& in, const string& out) {
		if (in.empty() || out.empty()) {
			throw std::invalid_argument(EXCEPT("Wrong filename"));
		}

		std::ifstream fin(in);

		if (!fin.is_open() || fin.eof()) {
			throw std::runtime_error(EXCEPT("File is not open"));
		}
		set<string> mediator;
		string temp;

		string::iterator cyle_iter;
		if (fin) {
			while (!fin.eof()) {
				getline(fin, temp);

				cyle_iter = remove_if(begin(temp), end(temp),
					[](const char& sym) {
					return sym == '\t' || sym == '\n';
				});
				temp.erase(cyle_iter, end(temp));
				if (temp.empty() || temp.size() < 2) {
					continue;
				}

				cyle_iter = begin(temp);
				while (*cyle_iter == ' ' && !temp.empty()) {
					temp.erase(cyle_iter);
				}

				mediator.insert(temp);
			}
		}
		mediator.erase("");
	
		std::ofstream fout(out);
		fout << mediator;
	}
	vector<string> SplitIntoWords(const string& str) {
		vector<string> result;

		auto str_begin = begin(str);
		const auto str_end = end(str);

		while (true) {
			auto it = find(str_begin, str_end, ' ');

			result.push_back(string(str_begin, it));

			if (it == str_end) {
				break;
			}
			else {
				str_begin = it + 1;
			}
		}
		return result;
	}
	bool is_contain(vector<string> lhs, vector<string> rhs) {
		vector<string> ret;
		std::sort(begin(lhs), end(lhs));
		std::sort(begin(rhs), end(rhs));
		std::set_intersection(begin(lhs), end(lhs),
			begin(rhs), end(rhs),
			std::inserter(ret, begin(ret)));
		return !ret.empty();
	}

	bool operator==(const string& lhs, const string& notif) {
		vector<bool> is_equal;

		if (lhs.size() != notif.size()) {
			if (is_contain(SplitIntoWords(lhs), SplitIntoWords(notif))) {
				return true;
			}
			int size = lhs.size() < notif.size() ? lhs.size() : notif.size();
			for (int i(0); i < size; i++) {
				if (lhs[i] == notif[i]) {
					is_equal.push_back(true);
				}
				else {
					is_equal.push_back(false);
				}
			}
		}
		else {
			for (size_t i(0); i < notif.size(); i++) {
				if (lhs[i] == notif[i]) {
					is_equal.push_back(true);
				}
				else {
					is_equal.push_back(false);
				}
			}
		}
		return std::count(begin(is_equal), end(is_equal), true) > (is_equal.size() / 2.f) ||
			is_contain(SplitIntoWords(lhs), SplitIntoWords(notif));
	}

	Knowledge::Knowledge(const string& filename, bool is_clear) {
		string db = GetOutStrTrash(filename) + "." + "temp.txt";
		std::ifstream fin;

		if (!is_clear) {
			GetOutTrash(filename, db);
			fin.open(db);
		}
		else {
			fin.open(filename);
		}

		if (!fin.is_open()) {
			throw std::runtime_error(EXCEPT("File is not open!"));
		}

		string temp_notion;

		if (fin) {
			while (!fin.eof()) {
				getline(fin, temp_notion);
				if (std::count(begin(temp_notion), end(temp_notion), '—') < 1) {
					continue;
				}
				auto it = find(begin(temp_notion), end(temp_notion), '—');
				not_to_dif.insert({ { begin(temp_notion), it - 1 },{ it + 2,end(temp_notion) } });
			}
		}
		if (!is_clear) {
			fin.close();
			system((string("del ") + db).c_str());
		}
	}
	Knowledge::Knowledge(const Knowledge& cp) {
		not_to_dif.clear();
		not_to_dif = cp.not_to_dif;
	}
	Knowledge& Knowledge::operator=(const Knowledge& val) {
		not_to_dif = val.not_to_dif;
		return *this;
	}
	Knowledge& Knowledge::operator+=(const Knowledge& val) {
		map<string, string> ret = not_to_dif;

		std::set_union(begin(not_to_dif), end(not_to_dif),
			begin(val.not_to_dif), end(val.not_to_dif), std::inserter(ret, begin(ret)));

		this->not_to_dif = ret;
		return *this;
	}
	Knowledge::~Knowledge() {
		if (not_to_dif.empty()) {
			return;
		}
		static int countobj = 1;
		std::ofstream fout("db" + std::to_string(countobj) + ".txt");
		countobj++;
		fout << not_to_dif;
	}


	map<string, string> Knowledge::find_dif(const string& notif) const noexcept {
		map<string, string> ret;

		for (const auto& item : not_to_dif) {
			if (item.first == notif) {
				ret.insert(item);
			}
		}
			return ret;
	}
	map<string, string> Knowledge::unde_the_letter(char letter) const {
		if (std::count_if(begin(not_to_dif), end(not_to_dif),
			[letter](const pair<string, string>& val) {
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
	map<string, string> Knowledge::GetSomeNotif(size_t n, const set<char>& letters) const{
		if (letters.empty() || n < letters.size()) {
			throw std::invalid_argument(EXCEPT("Invalid arguments"));
		}
		map<string, string> ret;
		srand(time(NULL));

		

		return ret;
	}
	map<string, string> Knowledge::GetSomeNotif(size_t n) const {
		map<string, string> ret;
		vector<pair<string, string>> val(begin(not_to_dif), end(not_to_dif));
		size_t size = not_to_dif.size();
		srand(time(NULL));
		
		for (size_t i(0); i < n; i++) {
			ret.insert(val[rand() % size]);
		}

		while (ret.size() < n) {
			map<string, string> temp = GetSomeNotif(n - ret.size());
			std::set_union(begin(ret), end(ret), 
				begin(temp), end(temp), 
				std::inserter(ret, end(ret)));
		}

		return ret;
	}
}