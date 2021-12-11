#include "bitstream.h"

#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>
using namespace std;

void bitstream::writeBit(u_char value){

    byte |= (value & 0x01) << pointer;

    if (pointer > 0){
        pointer--;
		return;
	}
	for(uint i=0 ; i<=7 ; i++)
         cout<< "byte: " << ((byte>>i) & 0x01) <<endl;

    write((char*)&byte, 1);
    pointer = 7;
    byte = 0;
}

void bitstream::writeNBits(u_char val, uint n) {
	uint bit;
	for (int i = n-1; i >= 0; i--) {
        bit = (val >> i%8) & 0x01;
    	writeBit(bit);
	}
}


void bitstream::writeNBits(u_char* val, uint n) {
	for (uint i = 0; i < n/8.0; i++) {
		if (i == n/8)
			writeNBits(val[i], n%8);	// escreve o que sobra do resto da divisão inteira por 8 (ultimo byte)
		else
			writeNBits(val[i], 8);		// escreve as 8 posições do byte
	}
}


u_char bitstream::readBit(){
	u_char bit;
	if(pointer < 0){
		read((char*)&byte, 1);
		pointer = 0;
	}
	bit = (byte >> pointer) & 0x01;
	pointer--;
	return bit;
}

u_char bitstream::readNBits(uint n){

	u_char value;
	for(int i = 0; i < n; i++){
		value = value << 1 | readBit();
	}
	return value;
}

void bitstream::readNBits(u_char* value, uint n){

	for (int i = 0; i < n/8.0; i++){
		if (i == n/32)
			value[i] = readNBits(n%8);
		else
			value[i] = readNBits(8);
	}
}

// void bitstream::addWhiteSpace(){
// 	for(int i = 0; i < pointer; i++){
// 		writeBit(0);
// 	}
// }

// bitstream::~bitstream() {
// 	if (writeMode)
// 		addWhiteSpace();
// 	close();
// }
