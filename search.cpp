#include "multiwin.h"
#include <QApplication>

#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream> 
#include <fstream> 

#include "util.h"
#include "myset.h"
#include "newparse.h" //NewParse p;
#include "webpage.h"
#include "searcheng.h"

int main(int argc, char* argv[])
{
	//char* fileName;
  if(argc < 2){
    	std::cerr << "Did not provide a CONFIGURATION FILE, using default 'config.txt'" << std::endl;
    	//std::string str = "config.txt";
		//fileName = strdup(str.c_str());
    return 0; 
  }
  
	QApplication app(argc, argv);
	//call on the window file passing in the filename
	Multiwin multiWindows(argv[1]);

	multiWindows.show(); 

	return app.exec();
	return 0; 
}