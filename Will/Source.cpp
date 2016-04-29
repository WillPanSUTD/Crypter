#include <assert.h>
#include <fstream>
#include <string>

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	string
		filename1 = "F:\\sutd\\Research\\prototypingProject\\programming\\result\\cc\\1.txt",     //directory&filename as input
		filename2 = "F:\\sutd\\Research\\prototypingProject\\programming\\result\\cc\\1.bin",	 //directory&filename of the binary file as output
		filename3 = "F:\\sutd\\Research\\prototypingProject\\programming\\result\\cc\\3.txt";		////read from binary to normal txt file
	string line;

	ifstream myfile(filename1);
	ofstream outputfile(filename2, ios::out | ios::binary);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
			outputfile << line << endl;
		}
		myfile.close();
	}

	else cout << "Unable to open file";


	outputfile.close();

	ifstream readfile(filename2, ios::in | ios::binary);

	if (readfile)
	{
		//readfile.seekg(0, readfile.end);
		int length = readfile.tellg();
		//readfile.seekg(0, readfile.beg);
		char * buffer = new char[length];


		////returns the number of bytes read.
		cout << readfile.gcount() << endl;
		cout << length << endl;
	//	readfile.read(buffer, sizeof(buffer));

		std::cout << "Reading " << length << " characters... ";
		// read data as a block:
		readfile.read(buffer, length);

		if (readfile)
			std::cout << "all characters read successfully.";
		else
			std::cout << "error: only " << readfile.gcount() << " could be read";
		readfile.close();

		// ...buffer contains the entire file...

	


		ofstream writefile(filename3, ios::trunc);

		writefile << buffer << endl;

		delete[] buffer;

	readfile.close();
	writefile.close();
	}




	return 0;
}

