#include "EXCEPT.h"

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