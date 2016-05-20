#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"
#include "newparse.h" 

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname);

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const;

  /**
   * Updates the set containing all unique words in the text
   */
  void all_words(const myset<std::string>& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  myset<std::string> all_words() const;

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  myset<WebPage*> incoming_links() const;

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  myset<WebPage*> outgoing_links() const;

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

  /**** Add other desired member functions here *****/

  void set_allLinks(myset<std::string>& set); 

  //modifyin the private variable visited -> true; 
  void visit(); 

  bool checkVisit(); 

  void setOldRank(double num); 

  double getOldRank(); 

  void setNewRank(double num); 

  double getNewRank(); 

 private:
  /**** Add other desired data members here *****/
  std::string fname; 
  // myset<WebPage*>  inLink; //pointers to pages that point to this webpages
  // myset<WebPage*>  outLink; //pointer to links to other pages 
  // myset<std::string>  allWords; 
  // myset<std::string>  allLinks;
  ///
  myset<WebPage*> inLink; //pointers to pages that point to this webpages
  myset<WebPage*> outLink; //pointer to links to other pages 
  myset<std::string> allWords; 
  myset<std::string> allLinks;
  NewParse p; //to call on the parser function 
  bool visited;
  double oldRank; 
  double newRank;  
  
};
#endif
