#pragma once
#ifndef _MENU_H
#define _MUNU_H

#include <iostream>
#include <string>

using std::string;

namespace MENU {
	void GeneralMenu() {
		std::cout << "1. Show all terms"	<< std::endl;
		std::cout << "2. Find the term"		<< std::endl;
		std::cout << "3. Get some terms"	<< std::endl;
		std::cout << "4. Dump to file"		<< std::endl;
		std::cout << "5. Get terms to day"	<< std::endl;
		std::cout << "6. Exit"				<< std::endl;
	}
	
	void LearnEnglish() {
		std::cout << "1. Choose the topic or kind of the words you are currently studying" << std::endl;
		// std::cout << "2. " << std::endl;
		std::cout << "2. Exit" << std::endl;
	}

	void Topics() {
		std::cout << "1. Nouns"			<< std::endl;
		std::cout << "2. Adjectives"	<< std::endl;
		std::cout << "3. Verbs"			<< std::endl;
		std::cout << "4. Adverbs"		<< std::endl;
		std::cout << "5. Discourse"		<< std::endl;
		std::cout << "6. From learning now list" << std::endl;
	}
}
using namespace MENU;
#endif // !_MENU_H