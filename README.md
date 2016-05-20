#Googletu

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

#What is GoogleTu
Created a simple search engine that implemented the PageRank Algorithm that is what Google was first known for. This program utilized:
* C++
* PageRank Algorithm
* Qt
* Merge Sort
* Templates

##Why
This was an assignment for one of my CS classes and I had thought that it was definetly one of the ones that was more challenging. This assignment required us to utilize the PageRank Algorithm and other algorithms such as merge sort.

##Name?
The reason why I named this assignment GoogleTu is because we had to use the ranking algorithm that made Google known, I decided to create a "second" version I guess you can say. My last name is said like the number "Two" so I was trying to be creative by naming it Google Two. I had used Adobe Photoshop to add on the additional tu letters.
