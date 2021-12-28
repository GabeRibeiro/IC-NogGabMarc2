#ifndef GOLOMB_H
#define GOLOMB_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>

#include "../BitStream/bitstream.h"

using namespace std;

class Golomb{
    public:
        int m, b;
        string unary(int q);
        string binary(int x, int n);
        int decimal(string a);

    //public:
        Golomb(int m);
        string encode(signed int n);
        int decode(string str);
        string  signed_encode(int n);
        int signed_decode(string code);
        void set_m(int m);
        int get_m(void);
        void write(vector<int> v, bitstream &b);
        vector<int> read(int elems, bitstream &b);
        void writeHdr( vector<int> v, bitstream &b);
        void writeHdr( vector<short> v, bitstream &b);
        vector<int> readHdr(int type, bitstream &b);

};

#endif