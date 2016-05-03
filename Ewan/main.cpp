#include <iostream>
#include <string>
#include <bitset>
#include <ctime>
#include <typeinfo>

using namespace std;
int main()
{

    /* RANDOM BIT STRING GENERATION */
  /*  int x[100];
    int i;
    srand(time(NULL));

    for(i=0;i<100;i++)
    {
    x[i] = rand() % 2;
    }

    /* MESSAGE INPUT FROM USER */
    std::string message;

    cout << "Enter Message:";
    getline (cin, message);

    /* CONVERSION TO BINARY AND ADDITION OF KEY */
    /* Get length of message, so we know how many bits to take from random string
       Add the key to each bit of the message */
    int msg_len = message.size();
    int msg_bin[msg_len];
    int i,j;
    int tmp;
    for (std::size_t i = 0; i < msg_len; i++)
  {



    (bool)bitset<8> (message.c_str()[i]);
  }

return 0;

  }
 /* int x = (bitset<8> (message[i])).to_ulong();
    cout<<x<<endl;
      cout << bitset<8>(message.c_str()[i]) << endl;*/
     /* tmp = bitset<8>(message.c_str()[i]);
      cout << tmp << endl;
      /*for (std::size_t j = 0; j < 8; j++)
(message.c_str()[i])).name()
     msg_bin[i][j] = bitset<8>(message.c_str()[i]);*/
  /*cout << msg_bin[2]<<endl;
   /* CONVERSION BACK TO PLAIN TEXT - SHOULD GIVE GOBBLEDIGOOK*/
