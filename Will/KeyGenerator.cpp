#include <assert.h>
#include <fstream>
#include <string>
#include <bitset>								//for future information, go to: http://www.cplusplus.com/reference/bitset/bitset/
#include <iostream>
using namespace std;

int main() {
	string filename = "F:\\sutd\\Research\\prototypingProject\\programming\\result\\cc\\key";   //Define a string to output a file.
	ofstream output(filename, ios::out|ios::binary);											//declare the output file
	int a;										//an integer to get the random number
	int N = 100;								//the size of key file

//	std::hash<std::bitset<16>> hash_fn;			//hash function for bitset, seems to generate 10 digits from a bitset<16> variable, I'm not so familiar with this. Can ignore if no need.

	if (output.is_open())						//test if the file is successfully opened
		for (int i = 0; i < N; i++)		//generate N keys 
		{
			a = rand();					//a is from  0 to RAND_MAX, here Rand_max is 32767
			std::bitset<16> b(a);		//transfrom a into bitset<16>;
			output << b << " ";			//output b to file, noted that I add a " " between two keys.
			//size_t h1 = hash_fn(b);
			//output << h1 << " ";
		}

	else
		cout << "error!" << endl;
	return 0;
}

