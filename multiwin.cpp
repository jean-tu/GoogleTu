#include <QVBoxLayout>
#include "multiwin.h"
#include "webpage.h"
#include "util.h" 
#include "msort.h"
#include <string>
#include <fstream> 
#include <sstream>  

//---------------Comparators-------------
    /* Comparing fileNames */
struct fileCompare{
  bool operator()(const WebPage* page1, const WebPage* page2){
    return (page1->filename() < page2->filename()); 
  }
};

    /* Comparing incoming links rank*/ 
struct inCompare {
  bool operator()(const WebPage* page1, const WebPage* page2){
    return (page1->incoming_links().size() < page2->incoming_links().size()); 
  }
};

    /* Comparing outgoing links rank*/ 
struct outCompare {
  bool operator()(const WebPage* page1, const WebPage* page2){
    return (page1->outgoing_links().size() < page2->outgoing_links().size());
  }
};

    /* Comparator for PageRank -->display the highest first*/
struct rankCompare {
  bool operator()(WebPage* page1, WebPage* page2) {
    return (page1->getNewRank() > page2->getNewRank()); 
  }
};


//---------------------------------------

Multiwin::Multiwin(std::string arg) : QWidget(NULL)
{
  //call on the parser 
  engine = new SearchEng;
  NewParse* p = new NewParse(); 
  this->parser(arg);
  engine->add_parse_from_index_file(newIndex, p);
  std::map<std::string, WebPage*> allPages = engine->getPages();


  //setting the title 
  this->setWindowTitle("GOOGLE II"); 
  //fixing  placement & width + height
  this->setGeometry(100,100, 600, 165); 
  //Overall Layout 
  overallLayout = new QVBoxLayout();  

  //Google Tu image 
  image.load("GoogleTu.png");
  imageContainer = new QLabel();
  imageContainer->setPixmap(QPixmap::fromImage(image));
  overallLayout->addWidget(imageContainer);

//searchLayout
  radioLayout = new QHBoxLayout(); 
  orRadio = new QRadioButton("OR", this); 
  andRadio = new QRadioButton("AND ", this);
  singleRadio = new QRadioButton("Single", this); 
  singleRadio->setChecked(true); 

  radioLayout->addWidget(singleRadio);
  radioLayout->addWidget(orRadio);
  radioLayout->addWidget(andRadio);
  overallLayout->addLayout(radioLayout);

  searchLayout = new QHBoxLayout();
  //search textbox
  textSearch = new QLineEdit();
  searchLayout->addWidget(textSearch); 

  //search Button 
  searchButton = new QPushButton("Search");
  searchLayout->addWidget(searchButton);
  overallLayout->addLayout(searchLayout);

//resultsLayout
   resultsLayout = new QHBoxLayout(); 

  //QTreeWidget to display the results  
  tree = new QTreeWidget;
  tree->setColumnCount(4);

  //setting the header of the TreeWidget 
  QStringList headerLabels;
  headerLabels.push_back("Filename"); 
  headerLabels.push_back("In Links"); 
  headerLabels.push_back("Out Links");
  headerLabels.push_back("Page Rank");  
  tree->setHeaderLabels(headerLabels);

  //sorting list button options
  sortList = new QVBoxLayout(); 
  sortLabel = new QLabel("Sort By: ");
  fileNameButton = new QPushButton("Filename");
  inLinkButton = new QPushButton("InLinks");
  outLinkButton = new QPushButton("OutLinks"); 
  pageRankButton = new QPushButton("Page Rank"); 
  sortList->addWidget(sortLabel); 
  sortList->addWidget(pageRankButton); 
  sortList->addWidget(fileNameButton); 
  sortList->addWidget(inLinkButton); 
  sortList->addWidget(outLinkButton);

  //The results list 
  resultsLayout->addWidget(tree);
  resultsLayout->addLayout(sortList); 
  //adding the layouts to overallLayout
  
  overallLayout->addLayout(resultsLayout);  
  //set the overall layout
  setLayout(overallLayout); 


  QVBoxLayout* mainLayout = new QVBoxLayout;
  overallLayout->addLayout(mainLayout);

  QVBoxLayout* otherLayout = new QVBoxLayout;
  otherWin = new QWidget;
  closeButton = new QPushButton("&Close Popup Window");
  otherLayout->addWidget(closeButton);
  exitButton = new QPushButton("&Exit Program"); 
  otherLayout->addWidget(exitButton); 
  overallLayout->addLayout(otherLayout);

//otherWin stuff 
  otherWin->setWindowTitle(""); 
  otherWin->setGeometry(300,200, 800, 600); 
  popupLayout = new QVBoxLayout();
  fileContent = new QTextEdit("");
  popupLayout->addWidget(fileContent);  

  //setting up bottom tier of the popup window; 
  bottom = new QHBoxLayout(); 
  inLayout = new QVBoxLayout(); 
  outLayout = new QVBoxLayout();
  sortButtons = new QVBoxLayout();  

  incomingLabel = new QLabel("Incoming");
  inList = new QTreeWidget();
  inLayout->addWidget(incomingLabel); 
  QStringList headerLabelsIn;
  headerLabelsIn.push_back("Filename"); 
  headerLabelsIn.push_back("In Links"); 
  headerLabelsIn.push_back("Out Links"); 
  inList->setHeaderLabels(headerLabelsIn);
  inLayout->addWidget(inList); 

  sortByLabel = new QLabel("SORT BY:"); 
  fSort = new QPushButton("filename");
  iSort = new QPushButton("input files");
  oSort = new QPushButton("output files"); 
  sortButtons->addWidget(sortByLabel); 
  sortButtons->addWidget(fSort); 
  sortButtons->addWidget(iSort); 
  sortButtons->addWidget(oSort); 

  outgoingLabel = new QLabel("Outgoing"); 
  outList = new QTreeWidget(); 
  outLayout->addWidget(outgoingLabel); 
  QStringList headerLabelsOut;
  headerLabelsOut.push_back("Filename"); 
  headerLabelsOut.push_back("In Links"); 
  headerLabelsOut.push_back("Out Links"); 
  outList->setHeaderLabels(headerLabelsOut);
  outLayout->addWidget(outList);
  
  bottom->addLayout(inLayout);
  bottom->addLayout(sortButtons); 
  bottom->addLayout(outLayout);
  popupLayout->addLayout(bottom);
  otherWin->setLayout(popupLayout); 
  
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(displayResults())); 
  QObject::connect(textSearch, SIGNAL(returnPressed()), this, SLOT(displayResults())); 
  QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(otherButtonClicked()));
  QObject::connect(fileNameButton, SIGNAL(clicked()), this, SLOT(fileSort())); 
  QObject::connect(inLinkButton, SIGNAL(clicked()), this, SLOT(inSort())); 
  QObject::connect(outLinkButton, SIGNAL(clicked()), this, SLOT(outSort())); 
  QObject::connect(pageRankButton, SIGNAL(clicked()), this, SLOT(prSort())); 
//pop up window     
  QObject::connect(fSort, SIGNAL(clicked()), this, SLOT(popFSort())); 
  QObject::connect(iSort, SIGNAL(clicked()), this, SLOT(popISort())); 
  QObject::connect(oSort, SIGNAL(clicked()), this, SLOT(popOSort())); 

  QObject::connect(inList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changeInLists(QTreeWidgetItem*)));
  QObject::connect(outList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changeOutLists(QTreeWidgetItem*)));

  QObject::connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(mainButtonClicked()));
  QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

}

Multiwin::~Multiwin(){
  qDeleteAll(this->overallLayout->findChildren<QWidget*>());
}

void Multiwin::mainButtonClicked()
{
  QTreeWidgetItem* item;// = tree->topLevelItem(1);
  QString temp;
  std::string temp2;  
  int numItems = tree->topLevelItemCount(); 
  for(int i = 0; i < numItems; i++){
    item = tree->topLevelItem(i); 
    if(item->isSelected()){
      temp =  item->text(i); 
      temp2 = temp.toStdString();//temp2 contains the filename that will be displayed
      break; 
    } 
    else{
      item = tree->currentItem(); 
      temp = item->text(i); 
      temp2 = temp.toStdString();
      break;
    }  
  }
  std::map<std::string, WebPage*> allPages = engine->getPages();

  otherWin->setWindowTitle(QString::fromStdString(temp2)); //setting the title to the 
  fileContent->clear();//clear what was once there 

//outputting the words to the textbox
  std::stringstream stream;
  stream << *allPages.find(temp2)->second ;
  std::string str =  stream.str();
  fileContent->setPlainText(QString::fromStdString(str)); 
  //fileContent->setWordWrap(true);
  
  inList->clear(); 
  outList->clear(); 
  inHits.clear(); 
  outHits.clear();

  myset<WebPage*> incominLinks = allPages.find(temp2)->second->incoming_links(); 
  for (myset<WebPage*>::iterator it = incominLinks.begin(); it != incominLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    inHits.push_back((*it));
  }

    myset<WebPage*> outgoinLinks = allPages.find(temp2)->second->outgoing_links(); 
  for (myset<WebPage*>::iterator it = outgoinLinks.begin(); it != outgoinLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    outHits.push_back((*it));
  }
  otherWin->show();
}
void Multiwin::otherButtonClicked()
{
  otherWin->hide();
}

void Multiwin::displayResults() {
  std::vector<WebPage*> result;
  //when the person doesn't have anything in the searchBox
  if(textSearch->text().isEmpty()){
    return; 
  }
  myset<std::string> toSearch; //set that holds the words to search 
  std::string enteredText = textSearch->text().toStdString(); 
  //lower all the characters in the string that the user inputs
  enteredText = convToLower(enteredText); 

  std::stringstream ss(enteredText); 
  std::string word; 
  tree->clear(); //clear things from the previous search 
  //things that will be displayed
  candidate.clear();
  //check the radio buttons that they clicked and see if they have the 
  //right number of words associated with them 
  if(orRadio->isChecked()){ //union
    myset<WebPage*> setUnion; 
    myset<WebPage*> set2; 
    //show pages w/ @least one of those given calls
    if(ss >> word) {
      toSearch.insert(word); 
      while(ss >> word) {
        toSearch.insert(word); 
      }
      setUnion = engine->getWebPages(*toSearch.begin()); 
      for(myset<std::string>::iterator it = toSearch.begin(); it != toSearch.end(); ++it){
        set2 = engine->getWebPages(*it); 
        setUnion = set2.set_union(setUnion);
      }
      //add the hits to the result vector 
      for(myset<WebPage*>::iterator it = setUnion.begin(); it != setUnion.end(); ++it){
        result.push_back(*it);
      }
    }
  }
  else if(andRadio->isChecked()){ //intersection
    myset<WebPage*> setIntersection; 
    myset<WebPage*> set1; 

    //Display the pages with those words
    if(ss >> word) {
      toSearch.insert(word); 
      while(ss >> word){
        toSearch.insert(word); 
      }
      setIntersection = engine->getWebPages(*toSearch.begin()); 
      for(myset<std::string>::iterator it = toSearch.begin(); it != toSearch.end(); ++it){
        set1 = engine->getWebPages(*it); 
        setIntersection = set1.set_intersection(setIntersection);
      }
      //add hits to the result vector 
      for(myset<WebPage*>::iterator it = setIntersection.begin(); it != setIntersection.end(); ++it){
        result.push_back(*it);
      }
    }
  }
  else { //single word is checked 
    //only take in ONE word from the textSearch ss 
    ss >> word; 
    myset<WebPage*> buffer = engine->getWebPages(word);
    for(myset<WebPage*>::iterator it = buffer.begin(); it != buffer.end(); ++it){
        result.push_back(*it);
      }
  }//end of else statement 
  std::set<WebPage*> checker; //checks to see if something has already been inserted 
  //new homework 6 -- Iterate through the results incoming & outgoing to create a candidate set
  for(unsigned int i = 0; i < result.size(); i++) {
    //candidate.push_back(result[i]); 
    std::set<WebPage*> incoming = result[i]->incoming_links(); 
    for(std::set<WebPage*>::iterator it = incoming.begin(); it != incoming.end(); ++it){
      if(checker.find(*it) == checker.end()){ //doesn't already exist in the set 
        checker.insert(*it); 
        candidate.push_back(*it); 
      }
    }
    std::set<WebPage*> outgoing = result[i]->outgoing_links(); 
    for(std::set<WebPage*>::iterator a = outgoing.begin(); a != outgoing.end(); ++a){
      if(checker.find(*a) == checker.end()){ //doesn't already exist in the set 
        checker.insert(*a); 
        candidate.push_back(*a); 
      }
    }
  }

  //create the map/GRAPH ------------------------------------------------------------------
  for(unsigned int i = 0; i < candidate.size(); i++){
    myset<WebPage*> newpages; 
    newpages.insert(candidate[i]); //creating the self-loop
    inPages[candidate[i]] = newpages; //setting the set to the item 
    myset<WebPage*> out = candidate[i]->outgoing_links();
    //check if the file is in the 
    for(myset<WebPage*>::iterator it = out.begin(); it != out.end(); ++it){
      //if the out going is in the results, put it in the map 
      if(std::count(candidate.begin(), candidate.end(), *it) > 0){
        newpages.insert(*it); 
      }
    }

    inPages[candidate[i]] = newpages;  //sets the set of webpages equal to the index 
  }
  tree->clear();
  //populating the tree by default pagerank
  this->prSort(); 
  //to clear the line that the user inputed
  textSearch->setText(""); 
}

//sort the Tree by filename
void Multiwin::fileSort(){
  tree->clear();
  //create the comparator

  fileCompare compare;
  mergeSort<WebPage* , fileCompare>(candidate, compare);
  for (unsigned int i = 0; i < candidate.size(); ++i) {   
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(candidate[i]->filename()));
    tree->addTopLevelItem(item);
    tree->setItemWidget(item, 1, new QLabel(QString::number(candidate[i]->incoming_links().size())));//setting colunn 2 
    tree->setItemWidget(item, 2, new QLabel(QString::number(candidate[i]->outgoing_links().size())));
    tree->setItemWidget(item, 3, new QLabel(QString::number(candidate[i]->getNewRank()))); //displaying the pagerank
  }
}

//sort the tree by # incoming links
void Multiwin::inSort(){
  tree->clear();
  //display
  inCompare compare; 
  mergeSort<WebPage* , inCompare>(candidate, compare);
  for (unsigned int i = 0; i < candidate.size(); ++i) {   
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(candidate[i]->filename()));
    tree->addTopLevelItem(item);
    tree->setItemWidget(item, 1, new QLabel(QString::number(candidate[i]->incoming_links().size())));//setting colunn 2 
    tree->setItemWidget(item, 2, new QLabel(QString::number(candidate[i]->outgoing_links().size())));
    tree->setItemWidget(item, 3, new QLabel(QString::number(candidate[i]->getNewRank()))); //displaying the pagerank
  }
}

//sort the tree by the # of Outgoing links
void Multiwin::outSort(){
  tree->clear();

  //display
  outCompare compare; 
  mergeSort<WebPage* , outCompare>(candidate, compare);
  for (unsigned int i = 0; i < candidate.size(); ++i) {   
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(candidate[i]->filename()));
    tree->addTopLevelItem(item);
    tree->setItemWidget(item, 1, new QLabel(QString::number(candidate[i]->incoming_links().size())));//setting colunn 2 
    tree->setItemWidget(item, 2, new QLabel(QString::number(candidate[i]->outgoing_links().size())));
    tree->setItemWidget(item, 3, new QLabel(QString::number(candidate[i]->getNewRank()))); //displaying the pagerank
  }
}

//sort the tree by the pagerank 
void Multiwin::prSort() {
  int n = candidate.size(); 
  tree->clear(); 
  //goes through and initialzes all of the nodes to 1/n probability [1st iteration]
  for( int i = 0; i < n; i++){ 
    candidate[i]->setOldRank(1.0/n);
    candidate[i]->setNewRank(0.0); 
  }
    for(int i = 1; i < timestep; i++){ //going through all of the timesteps 
        for(int node = 0; node < n; node++){ //for each node in the candidate set 
            double sum = 0.0; 
            //grab the incoming links 
            myset<WebPage*> newSet = candidate[node]->incoming_links();
            //adding the selfloop 
            newSet.insert(candidate[node]); 
            for(myset<WebPage*>::iterator it = newSet.begin(); it!= newSet.end(); ++it){
                //check to see if it is in the candidate set 
                if(count(candidate.begin(), candidate.end(), *it) > 0){ 
                    myset<WebPage*> newCand; 
                    for(unsigned int i = 0; i < candidate.size(); i++){
                        newCand.insert(candidate[i]); //to be able to do setIntersection
                    }
                    myset<WebPage*> intersect = inPages[*it].set_intersection(newCand);
                    sum = sum + ((*it)->getOldRank())*(1.0/intersect.size());
                }

            }
            candidate[node]->setNewRank(epsilon*(1.0/n) + (1.0-epsilon)*sum); //setting the newRank of the current 
        }
       // sets the newRank to OldRank 
        for(int a = 0; a < n; a++){
            candidate[a]->setOldRank(candidate[a]->getNewRank()); 
        }
    }
    
   //check if it sums to 1
    double total = 0; 
    for(unsigned int i = 0; i < candidate.size(); i++){

        total = total + candidate[i]->getOldRank(); 
    }
    std::cerr << "total value: " <<total << std::endl;


  //ranks
  rankCompare compare; 
  mergeSort<WebPage* , rankCompare>(candidate, compare);
  for (unsigned int i = 0; i < candidate.size(); ++i) {   
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(candidate[i]->filename()));
    tree->addTopLevelItem(item);
    tree->setItemWidget(item, 1, new QLabel(QString::number(candidate[i]->incoming_links().size())));//setting colunn 2 
    tree->setItemWidget(item, 2, new QLabel(QString::number(candidate[i]->outgoing_links().size())));
    tree->setItemWidget(item, 3, new QLabel(QString::number(candidate[i]->getNewRank()))); //displaying the pagerank
  
  }

}

//sort the popup window's ListWidget by filename
//both incoming and outgoing 
void Multiwin::popFSort(){
 inList->clear(); 
 outList->clear();
  fileCompare compare;
  mergeSort<WebPage* , fileCompare>(inHits, compare);
  mergeSort<WebPage* , fileCompare>(outHits, compare); 
  for(unsigned int i = 0; i < inHits.size(); i++){
    //inList->addItem(QString::fromStdString(inHits[i]->filename()));
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(inHits[i]->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number(inHits[i]->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number(inHits[i]->outgoing_links().size())));
  }
  for(unsigned int i = 0; i < outHits.size(); i++) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(outHits[i]->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number(outHits[i]->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number(outHits[i]->outgoing_links().size())));
  }
}


//sort the popup window's ListWidget by # incoming links 
void Multiwin::popISort(){
 inList->clear(); 
 outList->clear(); 
  inCompare compare;
  mergeSort<WebPage* , inCompare>(inHits, compare);
  mergeSort<WebPage* , inCompare>(outHits, compare);
  for(unsigned int i = 0; i < inHits.size(); i++) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(inHits[i]->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number(inHits[i]->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number(inHits[i]->outgoing_links().size())));
  }
  for(unsigned int i = 0; i < outHits.size(); i++) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(outHits[i]->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number(outHits[i]->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number(outHits[i]->outgoing_links().size())));
  }
}

//sort the popup window
void Multiwin::popOSort(){
  inList->clear();
  outList->clear();

  outCompare compare;
  mergeSort<WebPage* , outCompare>(outHits, compare); 
  mergeSort<WebPage* , outCompare>(inHits, compare); 
  for(unsigned int i = 0; i < inHits.size(); i++) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(inHits[i]->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number(inHits[i]->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number(inHits[i]->outgoing_links().size())));
  }
  for(unsigned int i = 0; i < outHits.size(); i++) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString(outHits[i]->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number(outHits[i]->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number(outHits[i]->outgoing_links().size())));
  }
}

//modify the information in the popup window 
void Multiwin::changeInLists(QTreeWidgetItem* item) { //inRow is the Column
  //QTreeWidgetItem* item;
  QString temp;
  std::string temp2;  
  int numItems = inList->topLevelItemCount(); 
  for(int i = 0; i < numItems; i++){
    item = inList->topLevelItem(i); 
    if(item->isSelected()){
      temp =  item->text(i); 
      temp2 = temp.toStdString();//temp2 contains the filename that will be displayed
      break; 
    } 
    else{
      item = inList->currentItem(); 
      temp = item->text(i); 
      temp2 = temp.toStdString();
      break;
    }  
  }
  std::map<std::string, WebPage*> allPages = engine->getPages();

  otherWin->setWindowTitle(QString::fromStdString(temp2)); //setting the title to the 
  fileContent->clear(); 
  std::stringstream stream;
  stream << *allPages.find(temp2)->second ;
  std::string str =  stream.str();
  fileContent->setPlainText(QString::fromStdString(str));
  inList->clear(); 
  outList->clear(); 
  inHits.clear(); 
  outHits.clear(); 
  myset<WebPage*> incominLinks = allPages.find(temp2)->second->incoming_links(); 
  for (myset<WebPage*>::iterator it = incominLinks.begin(); it != incominLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    inHits.push_back((*it));
  }

    myset<WebPage*> outgoinLinks = allPages.find(temp2)->second->outgoing_links(); 
  for (myset<WebPage*>::iterator it = outgoinLinks.begin(); it != outgoinLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    outHits.push_back((*it));
  }

}

//modify the information in the popup window 
void Multiwin::changeOutLists(QTreeWidgetItem* item) {
  QString temp;
  std::string temp2;  
  int numItems = outList->topLevelItemCount(); 
  for(int i = 0; i < numItems; i++){
    item = outList->topLevelItem(i); 
    if(item->isSelected()){
      temp =  item->text(i); 
      temp2 = temp.toStdString();//temp2 contains the filename that will be displayed
      break; 
    } 
    else{
      item = outList->currentItem(); 
      temp = item->text(i); 
      temp2 = temp.toStdString();
      break;
    }  
  }
  std::map<std::string, WebPage*> allPages = engine->getPages();

  otherWin->setWindowTitle(QString::fromStdString(temp2)); //setting the title to the 

  fileContent->clear(); 
  std::stringstream stream;
  stream << *allPages.find(temp2)->second ;
  std::string str =  stream.str();
  fileContent->setPlainText(QString::fromStdString(str)); 
  inList->clear(); 
  outList->clear(); 
  inHits.clear(); 
  outHits.clear(); 
  myset<WebPage*> incominLinks = allPages.find(temp2)->second->incoming_links(); 
  for (myset<WebPage*>::iterator it = incominLinks.begin(); it != incominLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    inList->addTopLevelItem(item);
    inList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    inList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    inHits.push_back((*it));
  }

    myset<WebPage*> outgoinLinks = allPages.find(temp2)->second->outgoing_links(); 
  for (myset<WebPage*>::iterator it = outgoinLinks.begin(); it != outgoinLinks.end(); ++it) {
    QTreeWidgetItem* item = new QTreeWidgetItem;
    //0 = filename, 1 = # incoming, 2 = # outgoing 
    item->setText(0, QString::fromStdString((*it)->filename()));
    outList->addTopLevelItem(item);
    outList->setItemWidget(item, 1, new QLabel(QString::number((*it)->incoming_links().size())));//setting colunn 2 
    outList->setItemWidget(item, 2, new QLabel(QString::number((*it)->outgoing_links().size())));
    outHits.push_back((*it));
  }
}

void Multiwin::parser(std::string fileName) {
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
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            index = index + trash[i]; 
                        }
                        else {
                            break; 
                        }
                    }
          }
          if(parameter == "OUTPUT_FILE"){
            ss >> trash;
                    //need to check if there are # after the file 
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            newIndex = newIndex + trash[i]; 
                        }
                        else {
                            break;
                        }
                    } 
          }
          else if(parameter == "STEP_NUMBER"){
            ss >> trash; 
                    for(unsigned int i = 0; i < trash.size(); i++) {
                        if(trash[i] != '#'){
                            timestep = atoi(trash.c_str());
                        }
                        else {
                            break; 
                        }
                    }
          }
          else if(parameter == "RESTART_PROBABILITY"){
            ss >> trash;
                    for(unsigned int i = 0; i < trash.size(); i++){
                        if(trash[i] != '#'){
                            epsilon = atof(trash.c_str());
                        }
                        else {
                            break;
                        }
                    }
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
}