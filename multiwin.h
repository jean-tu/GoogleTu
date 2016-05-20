#ifndef MULTIWIN_H
#define MULTIWIN_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget> 
#include <QTreeWidget> 
#include <QRadioButton>
#include <QHBoxLayout> 
#include <QVBoxLayout>
#include <QImage>
#include <QTextEdit> 
#include <sstream> 
#include <vector> 
#include <algorithm>

#include "searcheng.h"
#include "myset.h"

class Multiwin : public QWidget
{
  Q_OBJECT

public:
	//Multiwin(char*);
	Multiwin(std::string); 
	~Multiwin(); 

public slots:
  void mainButtonClicked();
  void otherButtonClicked();
  void displayResults(); 
  void fileSort(); 
  void inSort(); 
  void outSort(); 
  void prSort(); 

  void popFSort(); 
  void popISort(); 
  void popOSort();

  void changeInLists(QTreeWidgetItem* item); 
  void changeOutLists(QTreeWidgetItem* item);

private:
	//Everything should be pointers
		SearchEng* engine; 
	//Layout 
		QVBoxLayout* overallLayout;

	//searchLayout
		QHBoxLayout* searchLayout;

		//GoogleTu image 
		QImage image;
		QLabel* imageContainer;
		
		QHBoxLayout* radioLayout;
		QRadioButton* andRadio; 
		QRadioButton* orRadio;
		QRadioButton* singleRadio; 
		//top teir 
		QLineEdit* textSearch;
		QPushButton* searchButton;

		//Sorting options for SearchLayout
		QVBoxLayout* sortList;
		QLabel* sortLabel; 
		QPushButton* fileNameButton; 
		QPushButton* inLinkButton; 
		QPushButton* outLinkButton; 
		QPushButton* pageRankButton; 

	//resultsLayout 
		QHBoxLayout* resultsLayout; 
		
		// QListWidget* resultsList; 
		QTreeWidget* tree;

	//popupLayout
		QVBoxLayout* popupLayout;
		QHBoxLayout* bottom; 
		QTextEdit* fileContent;

		QVBoxLayout* inLayout; 
		QVBoxLayout* outLayout; 
		QVBoxLayout* sortButtons; 

		QLabel* incomingLabel; 
		QLabel* outgoingLabel;
		QLabel* sortByLabel;

		QTreeWidget* inList; 
		QTreeWidget* outList;  

		QPushButton* fSort; 
		QPushButton* iSort; 
		QPushButton* oSort; 

		//myset<WebPage*> result;
		std::map<std::string, WebPage*>* allPages;
		std::vector<WebPage*> candidate;
		std::vector<WebPage*> inHits; 
		std::vector<WebPage*> outHits; 
		//std::map<WebPage*, double> oldRank; 
		//std::map<WebPage*, double> finalRank; //for page rank

		//graph information 
		std::map<WebPage*, myset<WebPage*> > inPages; 
		

//given 
	QHBoxLayout* givenButtons;
	//QPushButton* mainButton;
	QWidget* otherWin;
	QPushButton* exitButton; 
	QPushButton* closeButton;

	void parser(std::string fileName);
	int timestep; 
	double epsilon; 
	std::string newIndex; 

};
#endif