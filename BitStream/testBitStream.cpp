#include "bitstream.h"

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <cassert>

using namespace std;

int main(int argc, char const *argv[])
{
    
    
    string filename = "testfile.bin";
    bitstream bs((char*) filename.data(), std::ios::binary|std::ios::in);
    bitstream bss((char*) filename.data(), std::ios::binary|std::ios::out);


    // bss.writeBit(0);
    // bss.writeBit(1);
    // bss.writeBit(1);
    // bss.writeBit(1);
    // bss.writeBit(0);
    // bss.writeBit(0);
    // bss.writeBit(0);
    // bss.writeBit(1);

    bss.writeNBits(65,16);

    bss.close();

    u_char a = bs.readNBits(8);

    cout << a << endl;



    return 0;
}