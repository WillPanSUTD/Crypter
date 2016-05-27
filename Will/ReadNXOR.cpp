#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <list>
using namespace std;

int main()
{
	string
		filename1 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\key",     //declare the directory of key file. Store the key we are about to use
		filename2 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\in",			//declare the directory of input message file. 
		filename3 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\out";			//declare the directory of output XOR result file.

	/////////////////////PART  ONE//////////////////////////////////////////////////////////////
	/////////////////////Read a text file (message)/////////////////////////////////////////////
	char *message, c;			////message is a pointer (point to an array of char, we will define its length later) 
	int length;					///length of message = number of char in the message
	ifstream  info(filename2);	////declare the file variable of input message file

	if (info.is_open())
	{
		info.seekg(0, info.end);////seekg is used here to make the file pointer go to the end of the file, so we can use tellg to tell the length of the file
		length = info.tellg();
		info.seekg(0, info.beg);////restore the pointer's position to the beginning of the file
		message = new char[length];	///so we get the length of the message
		int i = 0;
		while (info.get(c) && c != EOF)		//////get a char from info, and save it to c
			message[i++] = c;		//////c->message
		if (i != length)
			length = i;			///////////double-check and update the length

		cout << "the file is opened successfully, with " << length << " characters." << endl;
	}
	else
	{
		cout << "unable to open info file!";
		return 0;
	}
	info.close();



	//////////////////////////////PART TWO/////////////////////////////////////////////////////////////////////
	//////////////////////////////Read the key from the file we stored/////////////////////////////////////////
	fstream key(filename1);			///declare an input file pointer to file key
	bool KeyFlag = false;        ////////////determine whether key file should be appended or written
	list<bitset<8>> BitsetList;         						/////use to save the rest contents of key file, please google list c++ for further information
	bitset<8> xxx;					////a temporary variable
	char xxxn;
	char *keychar = new char[length];			//////////////////read the key char from key file
	int keysize = 0;

	if (key.is_open())
	{
		key.seekg(0, key.end);
		keysize = key.tellg();					////measure the length of key file
		key.seekg(0, key.beg);
		if (keysize > 0)						////test if key file size > 0, push all the key to the key list
			for (int i = 0; i < keysize; i++)
			{
				key.get(c);
				BitsetList.push_back(c);
			}
		key.seekg(0, key.beg);					////key.get(char) will change the position of file pointer, move it back to the begining
		cout << "The key file is opened successfully, with " << keysize << " keys" << endl;
		if (keysize > length)					////if the key file is larger than message, directly read keys from key file
		{
			cout << "Key number is larger than message number, directly read from key" << endl;
			for (int i = 0; i < length; i++)
			{
				//key.get(c);
				xxx = BitsetList.front();
				keychar[i] = static_cast<char>(xxx.to_ulong());
				BitsetList.pop_front();			////directly read from the list
				KeyFlag = false;
			}

		}
		else
		{
			cout << "Key number is smaller than message number, need to add more keys" << endl;
			KeyFlag = true;
		}
		key.close();
	}
	else
	{
		cout << "key file doesn't exist, unable to open key file!" << endl;
		KeyFlag = true;
	}




	/////////////////////////////PART THREE//////////////////////////////////////////////
	//////////////////////////////generate/append the key/////////////////////////////////////////////////////

	fstream output(filename1, ios::trunc | ios::out);	//declare the output file to store the key
	if (KeyFlag)												////need to generate or append the key
	{
		cout << "key generating/appending process!" << endl;
		cout << "original key length: " << BitsetList.size() << endl;

		char a;										//an integer to get the random number
		int N = 1000;								//the size of key file
		srand(time(NULL));
		for (int i = 0; i < N; i++)		//generate N keys 
		{
			a = rand();					//a is from  0 to RAND_MAX, here Rand_max is 32767
			std::bitset<8> b(a);		//transfrom a into bitset<8>;
	//		output << b << " ";			//output b to file, noted that I add a " " between two keys.
			BitsetList.push_back(b);			////push_back the bitset<8> b to bio vector class
		}
		if (output.is_open())						//test if the file is successfully opened
		{
			cout << "message length: " << length << endl;
			cout << "appended key length: " << BitsetList.size() << endl;
			
			for (int i = 0; i < length; i++)		///KeyFlag is true, keychar[i] must be empty, get length number of keys from bitset list
			{
				xxx = BitsetList.front();
				BitsetList.pop_front();
				c = static_cast<char>(xxx.to_ulong());
				keychar[i] = c;
			}
			while (!BitsetList.empty()) {
				xxx = BitsetList.front();
				xxxn=xxx.to_ulong();
				//output << xxx;
				output.write(reinterpret_cast<const char*>(&xxxn), sizeof(xxxn));			/////////write the rest bitset keys to key file
				BitsetList.pop_front();			//save the rest key to file
			}


		}
		else
			cout << "Error: Unable to update the key file!" << endl;

	}

	else												//no need to generate more keys, but have to save the rest keys to key file
	{
		cout << "Jumping part three!" << endl;
		while (!BitsetList.empty()) {		
			xxx = BitsetList.front();
			xxxn = xxx.to_ulong();
			//output << xxx;
			output.write(reinterpret_cast<const char*>(&xxxn),sizeof(xxxn));
			BitsetList.pop_front();			//save the rest key to file
		}
	}

	output.close();
	BitsetList.clear();

	//////////////////////////////PART FOUR//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////XOR operation and save the file in disk////////////////////////////////////////
	char *Encrypted_message;
	Encrypted_message = new char[length];

	bitset<8> result;						///////////////////////fist bitset is from key 

	for (int i = 0; i < length; i++)
	{
		bitset<8> first(keychar[i]);				//////////////////////Get a bitset
		bitset<8> second(message[i]);				///////////////////////second bitset from text (message)
		cout << first << " " << second << " " << message[i] << endl;
		result = first ^= second;														/////////////XOR operation
		xxxn = result.to_ulong();
		Encrypted_message[i] = static_cast<char>(xxxn);									//////transform bitset into char
		cout << "XOR result in binary: " << result << ", XOR result as text: " << Encrypted_message[i] << endl;
		//	cout << "haha!" << endl;
	}

	ofstream outfile(filename3, ios::out | ios::trunc);
	for (int i = 0; i < length; i++)
		outfile << Encrypted_message[i];					///write the output file
	outfile.close();



	///////////////////////////PART FIVE////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////decryption from the Encrypted_message and the key file from PART THREE //////////////////////


	///code part


	return 0;
}