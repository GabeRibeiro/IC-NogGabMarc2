#include "bitstream.h"

#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>
using namespace std;

void bitstream::writeBit(uint8_t value){
    byte |= (value & 0x01) << pointer;
    if (pointer > 0){
        pointer--;
		return;
	}
    write((char*)&byte, 1);
    pointer = 7;
    byte = 0;
}

void bitstream::writeNBits(uint8_t val, uint n) {
	uint bit;
	for (int i = n-1; i >= 0; i--) {
        bit = (val >> i%8) & 0x01;
    	writeBit(bit);
	}
}


void bitstream::writeNBits2(uint32_t* val, uint n) {
	for (uint i = 0; i < n/32.0; i++) {
		cout << "aa";
		cout << val[i] << endl;
		if (i == n/8)
			writeNBits(val[i], n%32);	// escreve o que sobra do resto da divisão inteira por 8 (ultimo byte)
		else
			writeNBits(val[i], 32);		// escreve as 8 posições do byte
	}
}


uint8_t bitstream::readBit(){
	uint8_t bit = 0;
	if(pointer < 0){
		read((char*)&byte, 1);
		//cout << "value readfile: " << byte << endl;
		pointer = 7;
	}
	//cout << "bit read: " << ((byte >> pointer) & 0x01) << endl;
	bit = ((byte >> pointer) & 0x01);
	pointer--;
	return bit;
}

void bitstream::readBit(uint8_t* bit) {
	if (pointer < 0) {
		read((char*)&byte, 1); 
		pointer = 7;
	}
	*bit = ((byte >> pointer) & 0x01);
	pointer--;
}

char* bitstream::readNBits(uint n){
	char* value = (char*)malloc((uint) n/8 + 1);
	for(uint i=0; i<n; i++){
		value[i/8] = value[i/8] << 1 | readBit();
		if(i==n-1 && n%8!=0) value[i/8] <<= (8-n%8);
	}
	return value;
}

string bitstream::toString(char* c, int n){
	string val;
	for(int i=0; i<n; i++)
		val+= ((int)((c[i/8] >> (7-i%8))&(0x01))==0? "0":"1");
	return val;
}

void bitstream::padding(){
	for(int i = 0; i < 7-pointer; i++){
		writeBit(0);
	}
}

// bitstream::~bitstream() {
// 	if (writeMode)
// 		addWhiteSpace();
// 	close();
// }
