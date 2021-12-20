#include "bitstream.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <bitset>
#include <cassert>

using namespace std;

char* decimalToBinary(uint32_t n);

int main(int argc, char const *argv[])
{
    
    
    string filename = "testfile.bin";
    bitstream bss((char*) filename.data(), std::ios::binary|std::ios::out);
    bitstream bs((char*) filename.data(), std::ios::binary|std::ios::in);

    // funciona
    /*
    bss.writeBit(0);
    bss.writeBit(1);
    bss.writeBit(1);
    bss.writeBit(1);
    bss.writeBit(0);
    bss.writeBit(0);
    bss.writeBit(0);
    bss.writeBit(1);
    bss.writeNBits(43,16);
    */

    string s[3] = {"01011100", "01001", "110101"};
    int i, j;

    for(i=0; i<3; i++){
        for(j=0; j<s[i].size(); j++){
            bss.writeBit( (s[i][j]=='0'? 0 : 1) );
        }
    }
    bss.padding();

    cout << endl;
    cout << endl;
    cout << endl;


    bss.close();

    
    char* a = bs.readNBits(17);
    

    for(int j=0 ; j<3 ; j++){
        for(int i=0 ; i<8 ; i++)
        {
            cout << ((a[j] >> i) & 0x01) << endl;
        }
        cout << a[j] << endl;
    }





    bs.close();
    
    return 0;
}
