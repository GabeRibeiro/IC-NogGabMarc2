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
    bss.writeBit(0);
    bss.writeBit(1);
    bss.writeBit(1);
    bss.writeBit(1);
    bss.writeBit(0);
    bss.writeBit(0);
    bss.writeBit(0);
    bss.writeBit(1);
    bss.writeNBits(43,16);


    bss.close();


    char* a = bs.readNBits(24);
    

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
