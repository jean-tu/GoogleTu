#Jean Tu 
##Homework 6: Project Part 3 

To compile the crawler: 
	You are going to need the .o files to compile the crawler.
	The crawler is in it's own folder in order to prevent the main's from conflicting with each other

	g++ -g -Wall bin/myset.o bin/newparse.o bin/searcheng.o bin/util.o bin/webpage.o crawler.cpp -o crawler

	I kind of didn't want to mess with the program because for the last homework I ran a qmake -project, qmake and tried running my program from there and it didn't really work. So I dind't want to do anything that would prevent it from compiiling, such as running it again since there are 2 mains from the crawler and the search.cpp. 

To run the crawler: 
	./crawler <config_file.txt> 
		If no <config_file.txt> is provided, then it will be defaulted to "config.txt"


To compile the program, type: 
	qmake
	make 

If the user does not provide a "config.txt" file when they are trying to run the program, I have a default "config.txt" 

To run the program with your config files type and it will take in the output file from the given config_file as the new index file for the ./hw6 program: 
	./hw6 <config_file.txt>

From what I understood from the assignment was that the crawler was supposed to be able to run on it's own and it is a stand alone. But from I also understood was that the homework6 file executable also takes in a config_file or else how would we be able to get the epsilon and the timestep value 