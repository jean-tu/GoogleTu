#include "newparse.h" 
#include <iostream> 
#include <string>
#include <fstream> 
#include <sstream> 

using namespace std; 

NewParse::NewParse() {

}

NewParse::~NewParse() {
	//calls on the vitrual deconstructor
}


void NewParse::parse(std::string filename, std::set<std::string>& allWords, 
	std::set<std::string>& allLinks){
	std::ifstream ifile(filename.c_str()); 
	if(ifile.fail()) {
		std::cout << "Could not open input file: " << filename << std::endl; 
	}
	std::string line; 
	std::string parenth; 
	std::string word; 
	std::string temp;
	std::string linkWord;  
	bool regularWord = true;
	bool bracket = false;  
	bool link = false;  
	while(getline(ifile, line)) {
		std::stringstream ss(line); 
		while(ss >> word){
			temp = ""; 
			parenth = ""; 
			//bracketParse(word, allWords, allLinks); 
			for(unsigned int i = 0; i < word.size(); i++) {
				word[i] = tolower(word[i]);
				if(word[i] == '['){ //know that this will be complete 
					//i++;
					bracket = true; 
					if(i > 0){ //if there is a word/char before the anchor 
						allWords.insert(temp); 
						temp = ""; 
					}
					i++;
					while(word[i] != ']'){
						word[i] = tolower(word[i]);
						if(i == (word.size()-1)){
							if(isalnum(word[i])){
								temp = temp + word[i];
							} 
							else{
								allWords.insert(temp); 
								temp = "";
							}
							allWords.insert(temp); 
							temp = "";
							ss >> word; 
							i = 0; 
							temp = tolower(word[i]); 
						}
						else if(isalnum(word[i])){
							temp = temp + word[i];
						} 
						i++;
					}
					if(bracket == true){
							allWords.insert(temp);
							bracket = false;  
							temp = "";
						}			 
					temp = ""; 
					i++;
					if(word[i] == '('){
						allWords.insert(temp);
						link = true; 
						i++;
						while(word[i] != ')'){
							linkWord = linkWord + word[i];
							i++; 
						}
						while(isalnum(word[i+1])){
							i++;
							temp = temp + word[i]; 
						}
						allWords.insert(temp); 
						temp = ""; 
					}
					if(link == true){ //there is a link, insert it 
						allLinks.insert(allLinks.end(), linkWord); 
						linkWord = "";
						link = false; 
					}
					temp = "";
					regularWord = false;  
				}
				else if(word[i] == '(') { //if it is a link_to_file
					if(i > 0) { //if not the first element 
						allWords.insert(temp); 
						temp = ""; 
					}
					regularWord = false; 
					allWords.insert(temp); 
					temp = ""; 
				}
				else if(word[i] == ')'){
					allWords.insert(temp); 
					temp = "";
					while(isalnum(word[i+1])){
							i++;
							temp = temp + word[i]; 
							//i++;
					}
					allWords.insert(temp); 
					temp = ""; 
				}
				else if(isalnum(word[i])) {
					temp = temp + word[i]; 
				}
				else { //catches spaces & special characters 
					allWords.insert(temp);
					temp = ""; 

				}
			}//end of for loop 
			if(regularWord == true) {
				allWords.insert(temp); 
				temp = ""; 
			}
			regularWord = true; 
		}//end of while(ss >> word) 
	}

}