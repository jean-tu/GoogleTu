#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);

  /**** Add other desired member functions here *****/
  std::map<std::string, WebPage* > getPages() const; //to return allPages; 
  const myset<WebPage*>& getWebPages(std::string); 

 private:
  /**** Add other desired data members here *****/
 	NewParse newparser; 
 	//filename, Webpage associated with it 
 	//string = data1.txt
 	//webpage* = an object webpage 
 	std::map<std::string, WebPage* > allPages; 
 	myset<WebPage*>  webpointers; //hold webpage pointers, so i can iterate through later
 	std::map<std::string, myset<WebPage*>  > word_to_setWeb;  
  myset<std::string> inserted; //stores the files that have already been searched 
};

#endif
