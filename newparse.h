#ifndef NEWPARSE_H
#define NEWPARSE_H
#include "pageparser.h" 

class NewParse:public PageParser {
	public: 
		NewParse(); 
		virtual ~NewParse(); //must be virtual when using inheritance 
		void parse(std::string filename, std::set<std::string>& allWords, 
	std::set<std::string>& allLinks);

		void bracketParse(std::string word, 
			std::set<std::string>& allWords, 
			std::set<std::string>& allLinks);

};
#endif