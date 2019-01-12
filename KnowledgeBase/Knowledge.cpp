#include "Knowledge.h"
#define CheckKnow "CheckKnow" // name of the repository of the already learned words
	
namespace Program {
	std::string GetOutFileType(std::string filename) {
		if (filename.empty()) {
			throw std::invalid_argument(EXCEPT("Wrond filename"));
		}

		auto it = std::find(begin(filename), end(filename), '.');
		filename.erase(it, end(filename));

		return filename;
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
		string temp = "";

		string::iterator cyle_iter; // just iterator for different use in the cycle
		if (fin) {
			while (!fin.eof()) {
				getline(fin, temp);

				cyle_iter = remove_if(begin(temp), end(temp),
					[](const char& sym) {
					return sym == '\t' || sym == '\n';	// while end of a string
				});
				temp.erase(cyle_iter, end(temp));		// delete all after end

				if (temp.empty() || temp.size() < 2) {	// is this string trash
					continue;
				}

				cyle_iter = begin(temp);
				while (*cyle_iter == ' ' && !temp.empty()) { // delete empty begin
					temp.erase(cyle_iter);
				}

				mediator.insert(temp); // only after all tests the string goes to the repository
			}
		}
		mediator.erase("");
	
		std::ofstream fout(out);
		fout << mediator;
	}
	vector<string> SplitIntoWords(const string& str) {
		vector<string> result;

		auto str_begin = begin(str);
		const auto str_end = end(str); // end iterator don't changes

		string::const_iterator it; // cycle iterator

		while (true) {
			it = find(str_begin, str_end, ' '); // find the gap

			result.push_back(string{ str_begin, it }); // convert interval from begin to the gap into string

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

		std::sort(begin(lhs), end(lhs)); // set_intersection does't working with unsorted vectors
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
			int size = lhs.size() < notif.size() ? lhs.size() : notif.size(); // find a smaller size
			for (int i(0); i < size; ++i) {
				if (lhs[i] == notif[i]) {
					is_equal.push_back(true);
				}
				else {
					is_equal.push_back(false);
				}
			}
		}
		else {
			for (size_t i(0); i < notif.size(); ++i) {
				if (lhs[i] == notif[i]) {
					is_equal.push_back(true);
				}
				else {
					is_equal.push_back(false);
				}
			}
		}
		return std::count(begin(is_equal), end(is_equal), true) > (is_equal.size() / 2.f) || // if more than half of the letters in a word match, the words are considered equal
			is_contain(SplitIntoWords(lhs), SplitIntoWords(notif)); // and if the strings contain the same words too
	}

	pair<string, string> Knowledge::DivideStr(const string& val) const{
		char divide = '–';
		if (std::count(begin(val), end(val), divide) < 1) {
			divide = '–';
		}
		if (std::count(begin(val), end(val), divide) < 1) {
			divide = '—';
		}


		if (std::count(begin(val), end(val), divide) < 1) {
			throw
				std::invalid_argument(
					EXCEPT(
						"This string is not consistenc with template: notiffication - diffinition")
				);
		}

		auto it = find(begin(val), end(val), divide);
		return { { begin(val), it - 1 }, { it + 2, end(val) } };
	}

	void Knowledge::FillRememberDiffFromFile() const{
		std::ifstream fin(CheckKnow);

		if (fin.is_open()) {
			string temp = "";
			while (!fin.eof()) {
				std::getline(fin, temp);
				try {
					UsedWords.insert(DivideStr(temp));
				}
				catch (...) {}
			}
		}
	}


	Knowledge::Knowledge(const Knowledge& cp) {
		term_to_dif.clear();
		term_to_dif = cp.term_to_dif;
	}
	Knowledge::Knowledge(const map<string, string>& cp) {
		if (!term_to_dif.empty()) { 
			term_to_dif.clear(); 
		}
		term_to_dif = cp;
	}
	Knowledge::Knowledge(const string& filename, ifc is_clear) {
		string TempFile = GetOutFileType(filename) + "." + "temp.txt";
		std::ifstream fin;

		if (is_clear == ifc::drt) { 
			GetOutTrash(filename, TempFile); // if the file is dirty clear file
			fin.open(TempFile); // create a temp file
		}
		else {
			fin.open(filename);
		}

		if (!fin.is_open()) {
			throw std::runtime_error(EXCEPT("File is not open!"));
		}

		string temp_notion = "";
			
		if (fin) {
			while (!fin.eof()) {
				getline(fin, temp_notion);
				try{
					if (term_to_dif.count(DivideStr(temp_notion).first) >= 1) {
						auto tmp = *term_to_dif.find(DivideStr(temp_notion).first);
						tmp.second.pop_back();
						string insert = tmp.second + "; " + DivideStr(temp_notion).second;
						
						term_to_dif.erase(tmp.first);
						term_to_dif.insert({ DivideStr(temp_notion).first, insert });
					}
					else {
						term_to_dif.insert(DivideStr(temp_notion));
					}
				}
				catch (...) {}
			}
		}
		if (is_clear == ifc::drt) {
			fin.close();
			system((string("del ") + TempFile).c_str()); // delete temp file
		}
	}
	Knowledge& Knowledge::operator=(const Knowledge& val) {
		term_to_dif = val.term_to_dif;
		return *this;
	}

	Knowledge Knowledge::operator+(const Knowledge& val) const noexcept {
		map<string, string> ret;
		std::set_union(begin(term_to_dif), end(term_to_dif),
			begin(val.term_to_dif), end(val.term_to_dif), std::inserter(ret, begin(ret)));
		return ret;
	}
	Knowledge& Knowledge::operator+=(const Knowledge& val) {
		return { *this = (*this + val) };
	}

	pair<string, string> Knowledge::operator[](size_t index) const {
		if (index > term_to_dif.size()) {
			throw std::out_of_range(EXCEPT("Index are more than the range size"));
		}

		size_t i = 0;
		for (const auto& item : term_to_dif) {
			if (i == index) {
				return item;
			}
			++i;
		}
	}

	int Knowledge::count(const string& dif) const {
		return count_if(begin(term_to_dif), end(term_to_dif),
			[dif](const pair<string, string>& val) {
			return val.first == dif;
		});
	}

	void Knowledge::DumpRemember2File() const {
		if (UsedWords.empty()) {
			return;
		}

		//time_t t = time(NULL);
		std::ofstream fout(CheckKnow);

		//fout << puts(ctime(&t)) << std::endl;
		fout << UsedWords << std::endl;
		//fout << "__________________________________________________________________________________________________________" << std::endl;
	}
	void Knowledge::DumpToFile(string FileName) const noexcept{
		if (term_to_dif.empty()) {
			return;
		}
		if (FileName == "") {
			static int countobj = 1;
			FileName = string("DumpToFile" + std::to_string(countobj) + ".txt");
			++countobj;
		}
		std::ofstream fout(FileName);
		fout << term_to_dif;

		DumpRemember2File();
	}

	void Knowledge::Add(const pair<string, string>& val) {
		if (val.first.empty() || val.second.empty()) {
			throw std::invalid_argument(EXCEPT("Invalid notification or diffinition"));
		}
		term_to_dif.insert(val);
	}
	void Knowledge::Remove(const string& key) {
		if (term_to_dif.empty()) {
			return;
		}
		//auto it = std::remove(begin(term_to_dif), end(term_to_dif), key);
		//term_to_dif.erase(it);
	}
	
	void Knowledge::DiffForDay(const string& FileName) const {
		FillRememberDiffFromFile();

		map<string, string> copy = term_to_dif; // just copy
		map<string, string> intersection; // intersection between a general repository and a repository of already used words

		std::set_intersection(begin(term_to_dif), end(term_to_dif),
			begin(UsedWords), end(UsedWords), std::inserter(intersection, begin(intersection)));

		map<string, string>::iterator it;

		for (const auto& item : intersection) {
			it = find(begin(copy), end(copy), item);
			copy.erase(it);
		}

		auto temp = Knowledge{ copy }.GetSomeNotif(25);
		
		std::ofstream fout(FileName);
		fout << temp;
		
		std::set_union(begin(UsedWords), end(UsedWords),
			begin(temp), end(temp), std::inserter(UsedWords, end(UsedWords)));

		DumpRemember2File();
	}
	
	map<string, string> Knowledge::FindDif(const string& notif) const {
		map<string, string> ret;

		for (const auto& item : term_to_dif) {
			if (item.first == notif) {
				ret.insert(item);
			}
		}

		return ret;
	}
	map<string, string> Knowledge::UndeTheLetter(char letter) const {
		if (std::count_if(begin(term_to_dif), end(term_to_dif),
			[letter](const pair<string, string>& val) {
			return val.first[0] == letter;
		}) < 1) {
			throw std::runtime_error(EXCEPT("Words unde the letter not found. May be wrong register"));
		}

		auto it = std::find_if(begin(term_to_dif), end(term_to_dif),
			[letter](const pair<string, string>& val) {
			return val.first[0] == letter;
		});

		auto it_end = it; // iterator for end of the letter range

		while (it_end != end(term_to_dif) && it_end->first[0] == letter) {
			++it_end;
		}
		return { it, it_end };
	}
	map<string, string> Knowledge::GetSomeNotif(size_t TermCount) const {
		if (TermCount > term_to_dif.size()) {
			throw std::invalid_argument(EXCEPT("Your number more then size of the base\a"));
		}
		if (TermCount == term_to_dif.size()) {
			return term_to_dif;
		}

		
		map<string, string> ret;
		vector<pair<string, string>> val(begin(term_to_dif), end(term_to_dif)); // duplicate to more comfortable use
		size_t size = term_to_dif.size(); // to reduce calculations

		srand(time(NULL));
		
		for (size_t i(0); i < TermCount; ++i) {
			ret.insert(val[rand() % size]);
		}

		while (ret.size() < TermCount) {
			map<string, string> temp = GetSomeNotif(TermCount - ret.size());
			std::set_union(begin(ret), end(ret), 
				begin(temp), end(temp), 
				std::inserter(ret, end(ret)));
		}

		return ret;
	}
}