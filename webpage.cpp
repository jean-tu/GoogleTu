#include "webpage.h"
#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <set> 
#include <map> 


WebPage::WebPage(){
  visited = false; 
  newRank = 0.0; 
  oldRank = 0.0; 
}

WebPage::WebPage(std::string filename){
  this->fname = filename; 
  visited = false; 
  newRank = 0.0; 
  oldRank = 0.0; 
}

WebPage::~WebPage(){

}

/**
 * Sets the filename/URL of this webpage
 */
void WebPage::filename(std::string fname){
  this->fname = fname; 
}

/**
 * Returns the filename/URL of this webpage
 */
std::string WebPage::filename() const{
  return fname; 
}

/**
 * Updates the set containing all unique words in the text
 */
void WebPage::all_words(const myset<std::string> & words){
    for(myset<std::string> ::iterator it = words.begin(); it != words.end(); ++it){
      allWords.insert(*it);
    }
}

/**
 * Returns all the unique, tokenized words in this webpage 
 */
myset<std::string>  WebPage::all_words() const{
  return allWords; 
}

/**
 * Adds a webpage that links to this page
 */
void WebPage::add_incoming_link(WebPage* wp){
  inLink.insert(wp); 
}

/**
 * Returns all webpages that link to this page
 */
myset<WebPage*>  WebPage::incoming_links() const{
  return inLink; 
}

/**
 * Adds a webpage that this page links to
 */
void WebPage::add_outgoing_link(WebPage* wp){
  outLink.insert(wp); 
}

/**
 * Returns all webpages this page links to
 */
myset<WebPage*>  WebPage::outgoing_links() const{
  return outLink; 
}

void WebPage::setOldRank( double num){
  oldRank = num; 
} 

double WebPage::getOldRank(){
    return oldRank; 
} 

void WebPage::setNewRank( double num){
  newRank = num; 
} 

double WebPage::getNewRank(){
    return newRank; 
} 

/**
 * Displays the webpage text to the screen 
 */
std::ostream & operator<< (std::ostream & os, const WebPage & page){
  std::string line; 
  std::string word; 
  std::string temp;
  std::string anchor; 
  bool anc = false; //if it's an anchor tag 
  std::ifstream ifile(page.filename().c_str());
  while(getline(ifile, line)) { 
    std::stringstream ss(line); 
    while(ss >> word) {
      temp = ""; 
      anchor = ""; 
      for(unsigned int i = 0; i < word.size(); i++) {
        anc = false; 
        if(word[i] == '['){ //so you know that it is a link text to be printed 
          anchor = "";
          os << temp; 
          temp = ""; 
          anchor = anchor + word[i]; 
          while(word[i] != ']'){
            word[i] = tolower(word[i]);
            if(i == (word.size()-1)){ //if on the last letter of word w/o ]
              if(isalnum(word[i])){
                anchor = anchor + word[i];
              } 
              os << anchor;
              anchor = "";
              ss >> word; 
              i = 0; 
              anchor = tolower(word[i]); 
            }
            else if(isalnum(word[i])){ //adding the letters in the anchor
              anchor = anchor + word[i];
            } 
            i++;
            // anchor = anchor + word[i];
            // i++; 
          }
          anc = true; 
          anchor = anchor + "]"; //+ word[i]; //grab the ]
          i++; 
          if(word[i] == '('){ 
            i++;
            while(word[i] != ')'){
              i++; 
            }
            //i++;
          }
          if(word[i+1] != '['){
            //i++;
          }
          if(word[i] != ')')
          {
            temp = temp + word[i];
          }
        }//end of bracket check 
        else{
          temp = temp + word[i]; 
        }
        if(anc == true){
          os << anchor; 
          anchor = ""; 
          anc = false; 
        }
      }//end of for loop
        os <<  temp;
        os << " ";  
        temp = ""; 
    } //end of while(ss>> word) loop 
    os << std::endl;
  }
  os << std::endl;
  return os; 
}

void WebPage::set_allLinks(myset<std::string> & set){
      for(myset<std::string> ::iterator it = set.begin(); it != set.end(); ++it){
      allLinks.insert(*it);
    }

}

void WebPage::visit(){
  this->visited = true; 
}

bool WebPage::checkVisit(){
  return this->visited; 
}