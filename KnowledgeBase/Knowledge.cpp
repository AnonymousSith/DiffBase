#include "Knowledge.h"
#define CheckNow "CheckKnow.txt"
	
namespace Program {
	RusAlphabet RusLetters;

	RusAlphabet::RusAlphabet() {
		letters = { 'À', 'Á', 'Â', 'Ã', 'Ä',
			'Å', '¨', 'Æ', 'Ç', 'È',
			'É', 'Ê', 'Ë', 'Ì', 'Í',
			'Î', 'Ï', 'Ð', 'Ñ', 'Ò',
			'Ó', 'Ô', 'Õ', 'Ö', '×',
			'Ø', 'Ù', 'Ú', 'Û', 'Ü',
			'Ý', 'Þ', 'ß' };
	}
	char RusAlphabet::get(int letterNumber) const {
		if (letterNumber <= 0 || letterNumber > 33) {
			throw std::invalid_argument(EXCEPT("Invalid number of letter"));
		}
		letterNumber--;
		return letters[letterNumber];
	}
	size_t RusAlphabet::size() const noexcept {
		return 33;
	}
	

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

	pair<string, string> Knowledge::DivideStr(const string& val) const{
		if (std::count(begin(val), end(val), '—') < 1) {
			throw 
				std::invalid_argument(
				EXCEPT(
				"This string is not consistenc with template: notiffication - diffinition")
			);
		}

		auto it = find(begin(val), end(val), '—');
		return { { begin(val), it - 1 }, { it + 2, end(val) } };
	}

	void Knowledge::PullRememberDiffIntoFile() const{
		std::ifstream fin(CheckNow);

		if (fin.is_open()) {
			string temp = "";
			while (!fin.eof()) {
				std::getline(fin, temp);
				try {
					ChechRemember.insert(DivideStr(temp));
				}
				catch (...) {}
			}
		}
	}


	Knowledge::Knowledge(const Knowledge& cp) {
		not_to_dif.clear();
		not_to_dif = cp.not_to_dif;
	}
	Knowledge::Knowledge(const map<string, string>& cp) {
		if (!not_to_dif.empty()) { 
			not_to_dif.clear(); 
		}
		not_to_dif = cp;
	}
	Knowledge::Knowledge(const string& filename, ifc is_clear) {
		string db = GetOutStrTrash(filename) + "." + "temp.txt";
		std::ifstream fin;

		if (is_clear == ifc::drt) {
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
				try{
					not_to_dif.insert(DivideStr(temp_notion));
				}
				catch (const std::exception& exc) {
					continue;
				}
			}
		}
		if (is_clear == ifc::drt) {
			fin.close();
			system((string("del ") + db).c_str());
		}
	}
	Knowledge& Knowledge::operator=(const Knowledge& val) {
		not_to_dif = val.not_to_dif;
		return *this;
	}

	Knowledge Knowledge::operator+(const Knowledge& val) const noexcept {
		map<string, string> ret;
		std::set_union(begin(not_to_dif), end(not_to_dif),
			begin(val.not_to_dif), end(val.not_to_dif), std::inserter(ret, begin(ret)));
		return ret;
	}
	Knowledge& Knowledge::operator+=(const Knowledge& val) {
		return { *this = (*this + val) };
	}

	pair<string, string> Knowledge::operator[](size_t index) const {
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

	int Knowledge::count(const string& dif) const {
		return count_if(begin(not_to_dif), end(not_to_dif),
			[dif](const pair<string, string>& val) {
			return val.first == dif;
		});
	}

	void Knowledge::DumpRemember2File() const {
		if (ChechRemember.empty()) {
			return;
		}

		std::ofstream fout(CheckNow);
		fout << ChechRemember << std::endl;
	}
	void Knowledge::DumpToFile(string FileName) const noexcept{
		if (not_to_dif.empty()) {
			return;
		}
		if (FileName == "") {
			static int countobj = 1;
			FileName = string("DumpToFile" + std::to_string(countobj) + ".txt");
			++countobj;
		}
		std::ofstream fout(FileName);
		fout << not_to_dif;

		DumpRemember2File();
	}

	void Knowledge::Add(const pair<string, string>& val) {
		if (val.first.empty() || val.second.empty()) {
			throw std::invalid_argument(EXCEPT("Invalid notification of diffinition"));
		}
		not_to_dif.insert(val);
	}
	void Knowledge::Remove(const string& key) {
		if (not_to_dif.empty()) {
			return;
		}
		//auto it = std::remove(begin(not_to_dif), end(not_to_dif), key);
		//not_to_dif.erase(it);
	}
	

	size_t Knowledge::usingLetters() const noexcept {
		if (not_to_dif.empty()) {
			return 0;
		}

		size_t count = 0;
		for (int i(1); i <= 33; ++i) {
			try {
				if (!unde_the_letter(RusLetters.get(i)).empty()) {
					++count;
				}
			}
			catch (const std::exception& exc) {
				continue;
			}
		}
		return count;
	}

	void Knowledge::DiffForDay(const string& FileName) const {
		PullRememberDiffIntoFile();

		map<string, string> intersection;

		std::set_intersection(begin(not_to_dif), end(not_to_dif),
			begin(ChechRemember), end(ChechRemember), std::inserter(intersection, begin(intersection)));

		std::ofstream fout(FileName);
		auto temp = Knowledge{ intersection }.GetSomeNotif(25);
		fout << temp;
		
		std::set_union(begin(ChechRemember), end(ChechRemember),
			begin(temp), end(temp), std::inserter(ChechRemember, end(ChechRemember)));

		DumpRemember2File();
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
		while (it_end != end(not_to_dif) && it_end->first[0] == letter) {
			++it_end;
		}
		return { it, it_end };
	}
	map<string, string> Knowledge::GetSomeNotif(size_t TermCount, size_t LettersCount) const{
		if (TermCount > not_to_dif.size() || TermCount < LettersCount * 30) {
			throw std::invalid_argument(EXCEPT("Invalid arguments"));
		}
		map<string, string> ret;
		vector<pair<string, string>> temp;
		srand(time(NULL));

		for (int i(1); i <= 33; ++i) {
			try {
				temp = { map<string, string>{ unde_the_letter(RusLetters.get(i)).begin(),
					unde_the_letter(RusLetters.get(i)).end() }.begin() , 
					map<string, string> { unde_the_letter(RusLetters.get(i)).begin(),
					unde_the_letter(RusLetters.get(i)).end() }.end() };
			}
			catch (const std::exception& exc) {
				continue;
			}

			if (temp.empty()) {
				continue;
			}

			int letcount = LettersCount > temp.size() ? temp.size() : LettersCount;
			for (int j(0); j < letcount; ++j) {
				ret.insert(temp[rand() % temp.size()]);
			}

		}
		while (ret.size() < TermCount * Knowledge{ ret }.usingLetters()) {
			map<string, string> temp = GetSomeNotif(TermCount - ret.size());
			std::set_union(begin(ret), end(ret),
				begin(temp), end(temp),
				std::inserter(ret, end(ret)));
		}

		return ret;
	}
	map<string, string> Knowledge::GetSomeNotif(size_t TermCount) const {
		map<string, string> ret;
		vector<pair<string, string>> val(begin(not_to_dif), end(not_to_dif));
		size_t size = not_to_dif.size();

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