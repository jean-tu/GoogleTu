#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream> 
#include <fstream> 
#include <iostream>
#include <vector> 
#include <map> 
#include "webpage.h"
#include "util.h"
#include <stdlib.h> 

void DFS(std::string fileName, std::ofstream& myfile);  
std::map<std::string, bool> files; 
std::map<std::string, WebPage*> allPages; 
std::set<std::string>* inserted; 

void parse(std::string filename, std::vector<std::string>& allWords, std::vector<std::string>& allLinks);

int main(int argc, char* argv[]){ 
std::string fileName;
  if(argc < 2){ //default "config.txt" will be used 
    	std::cerr << "Did not provide a CONFIGURATION FILE, using default 'config.txt'" << std::endl;
    	fileName = "config.txt";
  }
  else {// only gets one parameter
  	fileName = std::string(argv[1]); 
  }
  //create a parser for config.txt 
  std::ifstream ifile(fileName.c_str());
  if(ifile.fail()){
  	std::cerr << "COULD NOT OPEN 'config.txt'" << std::endl;
  }
  std::string line; 
  std::string buff; 
  std::string parameter; //check if equal to INDEX_FILE, or OUTPUT_FILE
  std::string value;
  std::string trash; 
  bool foundIndex = false; 
  std::string index; 
  int timestep = 0; 
  double epsilon = 0;
  std::string outputFile; 
  std::string trash2;  //to put the word in before you see the # 
  bool hashTag = false; 
  while(getline(ifile, line)) {
  	std::stringstream ss(line); 
  	hashTag = false; 
  	while(ss >> buff && hashTag == false){
  		for(unsigned int i = 0; i < buff.length(); i++) {
  			if( (buff[i] == '#')){
  				hashTag = true; 
  				break;
  			}
  			else if(buff[i] == '=') {
                trash = ""; 
  				//check to see if the word is 
  				if(parameter == "INDEX_FILE"){
					if(foundIndex == false){
                        ss >> trash;
                        foundIndex = true; 
                    }
                    ss >> trash2;
                    std::cerr << "trash2: " << trash2 << std::endl; 
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            index = index + trash[i]; 
                        }
                        else {
                            break; 
                        }
                    }
					std::cerr << "	index is: " << index << std::endl;
  				}
  				if(parameter == "OUTPUT_FILE"){
  					ss >> trash;
                    //need to check if there are # after the file 
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            outputFile = outputFile + trash[i]; 
                        }
                        else {
                            break;
                        }
                    } 
  			//std::cerr << "	outputfile is: " << outputFile << std::endl;
  				}
  				else if(parameter == "STEP_NUMBER"){
  					ss >> trash; 
                    for(unsigned int i = 0; i < trash.size(); i++) {
                        if(trash[i] != '#'){
                            timestep = atoi(trash.c_str());
                            //timestep = timestep + trash[i]; 
                        }
                        else {
                            break; 
                        }
                    }
  			//std::cerr << "	timestep : " << timestep << std::endl;
  				}
  				else if(parameter == "RESTART_PROBABILITY"){
  					ss >> trash;
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            epsilon = atof(trash.c_str());
                            //epsilon = epsilon + trash[i]; 
                        }
                        else {
                            break;
                        }
                    }
  			//std::cerr << "	restart percentage: " << epsilon << std::endl;
  				}
  				parameter.clear(); 
  			}
  			else {
  				if(buff[i] == ' '){
  					//do nothing
  				}
  				else{
  					parameter = parameter + buff[i]; 
  				}
  			}
  		}
  	}
  }	

  std::ofstream myfile;
  myfile.open(outputFile.c_str()); //whatever the user decides to put in);
  inserted = new std::set<std::string>; 
  std::ifstream newIfile(index.c_str());
  if(newIfile.fail()) {
    std::cout << "ERROR: Could not open index file!" << index << std::endl;
  }
//std::cerr << "before while loop" << std::endl;
  std::string file;
  while(getline(newIfile, file)){
   // std::cerr << "      Seed files: " << file << std::endl;
    DFS(file, myfile); 
  }

  myfile.close();
  return 0; 
}

void DFS(std::string fileName, std::ofstream& myfile){
  //cheDFSe, allWords, allLinks);
    for(unsigned int i = 0; i < allLinks.size(); i++) {
        DFS(allLinks[i], myfile); 
    } 
  } 
}
//copy of parse but with it takes in vectors 
void parse(std::string filename, std::vector<std::string>& allWords, std::vector<std::string>& allLinks){
    std::ifstream ifile(filename.c_str()); 
    if(ifile.fail()) {
        std::cout << "ERROR 404: Could not open " << filename << " or the page does not exist" << std::endl; 
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
                        allWords.push_back(temp); 
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
                                allWords.push_back(temp); 
                                temp = "";
                            }
                            allWords.push_back(temp); 
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
                            allWords.push_back(temp);
                            bracket = false;  
                            temp = "";
                        }            
                    temp = ""; 
                    i++;
                    if(word[i] == '('){
                        allWords.push_back(temp);
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
                        allWords.push_back(temp); 
                        temp = ""; 
                    }
                    if(link == true){ //there is a link, insert it 
                        allLinks.push_back(linkWord); 
                        linkWord = "";
                        link = false; 
                    }
                    temp = "";
                    regularWord = false;  
                }
                else if(word[i] == '(') { //if it is a link_to_file
                    if(i > 0) { //if not the first element 
                        allWords.push_back(temp); 
                        temp = ""; 
                    }
                    regularWord = false; 
                    allWords.push_back(temp); 
                    temp = ""; 
                }
                else if(word[i] == ')'){
                    allWords.push_back(temp); 
                    temp = "";
                    while(isalnum(word[i+1])){
                            i++;
                            temp = temp + word[i]; 
                            //i++;
                    }
                    allWords.push_back(temp); 
                    temp = ""; 
                }
                else if(isalnum(word[i])) {
                    temp = temp + word[i]; 
                }
                else { //catches spaces & special characters 
                    allWords.push_back(temp);
                    temp = ""; 

                }
            }//end of for loop 
            if(regularWord == true) {
                allWords.push_back(temp); 
                temp = ""; 
            }
            regularWord = true; 
        }//end of while(ss >> word) 
    }

}