#include "Knowledge.h"
	
namespace Program {
	void GetOutRabish(const string& in, const string& out) {
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
		fin.close();

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
			return false;
		}
		for (size_t i(0); i < notif.size(); i++) {
			if (tolower(lhs[i]) == tolower(notif[i])) {
				is_equal.push_back(true);
			}
			else {
				is_equal.push_back(false);
			}
		}
		return std::count(begin(is_equal), end(is_equal), true) > (is_equal.size() / 2) ||
			is_contain(SplitIntoWords(lhs), SplitIntoWords(notif));
	}

	Knowledge::Knowledge(const string& filename) {
		string DB_name = "db.txt";
		GetOutRabish(filename, DB_name);
		std::ifstream fin("db.txt");

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
				not_to_dif.insert({ { begin(temp_notion), it-1 },{ it+2,end(temp_notion) } });

				//temp_notion.clear();
				//temp_diff.clear();
			}
		}
	}

	vector<pair<string, string>> Knowledge::find_dif(const string& notif) const noexcept {
		vector<pair<string, string>> ret;

		for (const auto& item : not_to_dif) {
			if (item.first == notif) {
				ret.push_back(item);
			}

			/*if (item.first.size() != notif.size()) {
				if (is_contain(SplitIntoWords(item.first), SplitIntoWords(notif))) {
					ret.push_back(item);
				}
				continue;
			}
			else {
				for (size_t i(0); i < notif.size(); i++) {
					if (tolower(item.first[i]) == tolower(notif[i])) {
						is_equal.push_back(true);
					}
					else {
						is_equal.push_back(false);
					}
				}
			}
			if ((std::count(begin(is_equal), end(is_equal), true) > (is_equal.size() / 2)) ||
				is_contain(SplitIntoWords(item.first), SplitIntoWords(notif))) {
				ret.push_back(item);
			}
			is_equal.clear();
		}*/
		}
			return ret;
	}
}