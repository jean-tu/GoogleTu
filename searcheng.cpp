#include "searcheng.h" 
#include "webpage.h"
#include <iostream>  
#include <fstream> 
#include <set> 

using namespace std; 

SearchEng::SearchEng(){

}

SearchEng::~SearchEng(){
	//delete the Webpage* made in the add_parse_page section 
	//iterate through the set of webapges and delete
	for(map<string, WebPage*>::iterator it = allPages.begin(); it != allPages.end(); ++it){
		delete it->second;		
	}

}

void SearchEng::add_parse_from_index_file(string index_file, PageParser* parser){
	//create new webpages from each file 
	ifstream ifile(index_file.c_str()); 
	if(ifile.fail()) {
		cout << "Could not open input file" << std::endl; 
	}
	//string fname; 
	string buffer = ""; 
	vector<string> files;
	while(getline(ifile, buffer)){
		files.push_back(buffer); 
		//call the parser or constructor on the file name 
		this->add_parse_page(buffer, parser); 
		buffer = ""; 
	}
	//sort incoming & outcoming 
	//look through the map word_to_setWeb and 
}

void SearchEng::add_parse_page(string filename, PageParser* parser){
	// if(inserted.find(filename) != inserted.end()) { //the page has already been searched 
	// 	return; 
	// }
	// else {
	// 	inserted.insert(filename); 
	// }
	//creating the new Webpage
	WebPage* newpage;
	//need to check if the filename already exists  
	if(allPages.find(filename) != allPages.end()){
		newpage = allPages.find(filename)->second; 
	}
	else{ 
		newpage = new WebPage(filename);
		allPages[filename] = newpage; 
	} 

	//creating the needed members
	myset<std::string>  allWords; 
	myset<std::string>  allLinks; 
	set<string> name_of_file; 
	//parses the file
	parser->parse(filename, allWords, allLinks); 
	//setting all_words from the file into Webpage*
	newpage->all_words(allWords);  

	//setting incoming links
	for(myset<std::string> ::iterator it = allLinks.begin(); it != allLinks.end(); ++it){
		name_of_file.insert(*it); 
		//find the Webpage* from the filename
		if(allPages.find(*it) != allPages.end()){
			//cerr << "*it is " << *it << endl;
			//adding the incoming link
			allPages.find(*it)->second->add_incoming_link(newpage); 
			//adding the outgoing link
			allPages.find(newpage->filename())->second->add_outgoing_link(allPages.find(*it)->second);
			allPages.find(newpage->filename())->second->all_words(allWords); 
		}
		else { //the page doesn't exist, create it, then add it
			WebPage* pagenew = new WebPage(*it); 
			allPages[*it] = pagenew; //adding the new page
			allPages.find(*it)->second->add_incoming_link(newpage);
			//add the outgoing link
			allPages.find(newpage->filename())->second->add_outgoing_link(allPages.find(*it)->second);
			allPages.find(newpage->filename())->second->all_words(allWords); 
			
		}
	}
	//adding the webpage to the map of string to webpage* 
	webpointers.insert(newpage);//how you would know if the newpage exists 

	myset<std::string> ::iterator allWordsit; 
	for(allWordsit = allWords.begin(); allWordsit != allWords.end(); ++allWordsit) {
		//if the word already exists 
		if(word_to_setWeb.find(*allWordsit) != word_to_setWeb.end()){
			//then the key already exists 
			 word_to_setWeb.find(*allWordsit)->second.insert(newpage);//insert the page into the existing one
		}
		else {
			//create a set 
			myset<WebPage*>  newWebpageSet;// = new myset<WebPage*> (); 
			newWebpageSet.insert(newpage); //adding this page as a pointer for the string to Webpage*
			word_to_setWeb[*allWordsit] = newWebpageSet; 
		}
	}	
}

std::map<std::string, WebPage* > SearchEng::getPages() const{
	return allPages;
}

const myset<WebPage*> & SearchEng::getWebPages(string word) {
	return word_to_setWeb[word]; 
} 