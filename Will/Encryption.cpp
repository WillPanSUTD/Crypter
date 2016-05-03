#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>


using namespace std;

int main(int argc, char *argv[])
{
	ifstream in_stream;
	string filein, fileout, key;
	ofstream out_stream;
	int e;

	cout << "Enter the name of the file\n";
	cin >> filein; //User inputs incoming file name
	in_stream.open(filein.c_str(), ios::in | ios::binary); //Open the file

	string str((istreambuf_iterator<char>(in_stream)), istreambuf_iterator<char>());

	cout << "Enter the encryption key\n";
	cin >> key; //User inputs the key


	cout << "Enter the name of the outgoing file\n";
	cin >> fileout; //User inputs the outgoing file name
	out_stream.open(fileout.c_str(), ios::out | ios::binary); //Opens the file

	int L = key.size(); //Declaring the size of the key

	for (int i = 0; i<str.size(); i++) //Loop for the encryption
	{
		{out_stream << char(str[i] ^ key[i%L]); }
	} //XOR encryption  


	in_stream.close(); //close the incoming file
	out_stream.close();   //close the outgoing file


	system("PAUSE");
	return EXIT_SUCCESS;
}