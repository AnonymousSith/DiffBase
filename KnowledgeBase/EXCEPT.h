#pragma once
#ifndef _EXCEPT_H
#define _EXCEPT_H

#include <algorithm>
#include <iterator>
#include <string> 

std::string GetFilename(std::string);

#define EXCEPT(X) (X) + ((std::string("\a\nFile: ") + GetFilename(__FILE__) + "\nFunc: " + __func__ + "()" + "\nLine: " + std::to_string(__LINE__)))

#endif // !_EXCEPT_H