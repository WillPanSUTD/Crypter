#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <assert.h>
#include <string.h>
using namespace std;

////////////////////////It's a bitset template class I downloaded from http://codereview.stackexchange.com/questions/67012/easy-bitset-i-o, which could make coding easier I guess. 
///////////////////////Antoher alternative is http://codereview.stackexchange.com/questions/67350/easy-bit-io-very-simple-interface-works-up-to-n-64, I didn't use, you make take a try.
//////////////////////////If you feel hard to read this, jump to line 111. Or search "int main()".

template <std::size_t N>		//////Please google template definition, which enables the possibility of a class with multiple types. Here, BitIo<8>, BitIo<16>, ... etc. 	
class BitIo
{
public:							////Only functions and varibles defined as public can be called.

	void push_back(const std::bitset<N>& bs)
	{
		std::vector<Byte> result((N + 7) >> 3);
		for (std::size_t j = 0; j < N; ++j) {
			result[j >> 3] |= (bs[j] << (j & 7));
		}
		for (const Byte& byte : result) {
			bytes.push_back(byte);
		}
		num_bytes += NUM_BYTES_PER_BITSET;
	}

	std::bitset<N> pop_front()
	{
		std::bitset<N> result;
		for (std::size_t j = 0; j < N; ++j) {
			result[j] = ((bytes[(j >> 3) + offset] >> (j & 7)) & 1);
		}
		offset += NUM_BYTES_PER_BITSET;
		num_bytes -= NUM_BYTES_PER_BITSET;
		return result;
	}

	bool empty()
	{
		return num_bytes < NUM_BYTES_PER_BITSET;
	}

	void clear()
	{
		bytes.clear();
		num_bytes = 0;
	}

	std::size_t size()
	{
		return num_bytes;
	}

private:

	using Byte = unsigned char;
	static constexpr std::size_t NUM_BYTES_PER_BITSET = N / 8;

	template <std::size_t T>
	friend std::ostream& operator<<(std::ostream& os, const BitIo<T>& bio);
	template <std::size_t T>
	friend std::istream& operator >> (std::istream& is, BitIo<T>& bio);

	std::istream& read_file(std::istream& is)
	{
		bytes.clear();

		std::streampos current_pos, file_size;
		current_pos = is.tellg();
		is.seekg(0, std::ios::end);
		file_size = is.tellg() - current_pos;
		is.seekg(current_pos, std::ios::beg);

		bytes.resize(file_size);
		is.read(reinterpret_cast<char *>(&bytes[0]), file_size);

		num_bytes += file_size;

		return is;
	}

	std::vector<Byte> bytes;
	std::size_t offset = 0;
	std::size_t num_bytes = 0;
};

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const BitIo<N>& bio)
{
	for (const auto& byte : bio.bytes) {
		os << byte;
	}
	return os;
}

template <std::size_t N>
std::istream& operator >> (std::istream& is, BitIo<N>& bio)
{
	if (!is) {
		is.setstate(std::ios::failbit);
	}
	bio.read_file(is);
	return is;
}




int main()
{
	string
		filename1 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\key.bin",     //declare the directory of key file. Store the key we are about to use
		filename2 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\in",			//declare the directory of input message file. 
		filename3 = "f:\\sutd\\research\\prototypingproject\\programming\\result\\cc\\out";			//declare the directory of output XOR result file.

	BitIo<16> bio;				///the class I defined above, to make coding with bitset variable easier


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
		while (info.get(c))			//////get a char from info, and save it to c
			message[i++] = c;		//////c->message
	}
	else
	{
		cout << "unable to open info file!";
		return 0;
	}
	info.close();

	/////////////////////////////PART TWO//////////////////////////////////////////////
	//////////////////////////////generate the key/////////////////////////////////////////////////////
	ofstream output(filename1, ios::trunc | ios::binary);											//declare the output file to store the key
	int a;										//an integer to get the random number
	int N = length;								//the size of key file

	//	std::hash<std::bitset<16>> hash_fn;			//hash function for bitset, seems to generate 10 digits from a bitset<16> variable, I'm not so familiar with this. Can ignore if no need.

	for (int i = 0; i < N; i++)		//generate N keys 
	{
		a = rand();					//a is from  0 to RAND_MAX, here Rand_max is 32767
		std::bitset<16> b(a);		//transfrom a into bitset<16>;
//		output << b << " ";			//output b to file, noted that I add a " " between two keys.
		bio.push_back(b);			////push_back the bistet<16> b to bio vector class

		//size_t h1 = hash_fn(b);
		//output << h1 << " ";
	}
	if (output.is_open())						//test if the file is successfully opened
		output << bio;							//save bio vector to file
	else
		cout << "error!" << endl;
	output.close();

	cout << bio.size() << endl;
	//bio.clear();


	////////////////////////////////PART THREE (OPTIONAL)///////////////////////////////////////////////////////////////////
	////////////////////////////////Read the key from the file we stored/////////////////////////////////////////
	//fstream key(filename1, ifstream::in | ifstream::binary);			///declare an input file pointer to file key
	//BitIo<16> bio2;				

	//if (key.is_open())
	//{
	//	key >> bio2;									/////read from key file, save in bio2 vector
	//	while (!bio2.empty()) {
	//		cout << bio2.pop_front() << endl;			// Prints the all the keys (16-bit bitsets) in correct order.
	//	}
	//}
	//else cout << "unable to open key file!";
	//bio2.clear();

	//key.close();


	//////////////////////////////PART FOUR//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////XOR operation and save the file into out////////////////////////////////////////
	char *Encrypted_message;
	Encrypted_message = new char[length];

	bitset<16> first,result;						///////////////////////fist bitset is from key 
			
	for (int i = 0; i < length; i++)
	{
		first = bio.pop_front();					//////////////////////Get a bitset
		bitset<16> second(message[i]);				///////////////////////second bitset from text (message)
	//	cout << first << " " << second <<" "<< message[i]<< endl;
		result = first ^= second;														/////////////XOR operation
		unsigned long x=result.to_ulong();
		Encrypted_message[i] = static_cast<char>(x);									//////transform bitset into char
	//	cout << "XOR result in binary: "<<result<<", XOR result as text: "<< Encrypted_message[i] << endl;
	//	cout << "haha!" << endl;
	}

	ofstream outfile(filename3, ios::out);
	for (int i = 0; i < length; i++)
		outfile << Encrypted_message[i];
	outfile.close();



	///////////////////////////PART FIVE////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////decryption from the Encrypted_message and the key file from PART THREE //////////////////////
	
	
	///code part


	return 0;
}