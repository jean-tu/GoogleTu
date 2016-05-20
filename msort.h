#include <iostream> 
#include <vector> 
#include <stdint.h>

template<class T, class Comparator>
void mergeSort (std::vector<T>& vector1, Comparator comp)
{
	//when you are only dealing with one element
	if(vector1.size() == 1){
		return; 
	}
	//sort it if there are more than one 
	if(vector1.size() > 1) {
		int size = vector1.size()/2; 
		std::vector<T> vector2;
		std::vector<T> vector3;
		//making the left half of the array
		for(int i = 0; i < size; i++) {
			vector2.push_back(vector1[i]);
		}
		//making the right half of the array
		for(int i = size; i < vector1.size(); i++) {
			vector3.push_back(vector1[i]); 
		}

		//call mergeSort on the 2 1/2's
		mergeSort(vector2, comp); 
		mergeSort(vector3, comp); 


		mergeHelper(vector1, vector2, vector3, comp);
	} 
}

template<class T, class Comparator>
void mergeHelper(std::vector<T>& vector1,std::vector<T>& vector2,
	std::vector<T>& vector3, Comparator comp) {

		//grab the size of the 2 1/2 vectors
		int size2 = vector2.size(); 
		int size3 = vector3.size(); 

		//initialize the vector size
		int i = 0; //vector2 init
		int j = 0; //vector3 init
		int k = 0; //the size for vect1

		//while there are still elements in both of the vectors
		while(i < size2 && j < size3) {
			//inserts the left element if it's smaller
			if(comp(vector2[i], vector3[j])) {
				vector1[k] = vector2[i]; 
				i++; 
				k++; 
			}
			else {
				vector1[k] = vector3[j];
				j++; 
				k++;
			}
		}
		//if there are only elements left in the vect2
		while(i < size2) {
			vector1[k] = vector2[i];
			i++; 
			k++; 
		}
		//if there are only elements left in vect3
		while(j < size3) {
			vector1[k] = vector3[j];
			j++; 
			k++; 
		}
}