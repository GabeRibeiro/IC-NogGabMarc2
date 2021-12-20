#include "bitstream.h"

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

// uint32_t bitstream::readNBits(uint n) {
// 	assert(n <= 32);
// 	uint32_t value = 0;
// 	for (uint i = 0; i < n; i++) {
// 		value = value << 1 | readBit();
// 	}
// 	return value;
// }

char* bitstream::readNBits(uint n)
    {
        //n = n&0xFFFF; // para uint_32
        char* value = (char*)malloc((uint) n/8 + 1);
        for(int j = 0; j*8 < n; j++){
            for (uint i = 0; i < 8; i++) {
                value[j] = value[j] << 1 | readBit();
            }
        }
        return value;
    }

// char* bitstream::readNBits(uint n) {
// 	assert(n <= 32);
// 	char* value = (char*)malloc(sizeof(char) * (uint) n/8 + 1);
// 	for(int j = 0; j*8 < n; j++){
// 		for (uint i = 0; i < 8; i++) {
// 			value[j] = value[j] << 1 | readBit();
// 		}
// 	}
// 	return value;
// }

// void bitstream::readNBits2(uint32_t* value, uint n){

// 	for (uint i = 0; i < n/32.0; i++){
// 		if (i == n/32)
// 			value[i] = readNBits(n%32);
// 		else
// 			value[i] = readNBits(32);
// 	}
// }

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
