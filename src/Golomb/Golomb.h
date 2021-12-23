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
        int m;
        int b;
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
        void write(string fname, vector<int> v);
        vector<int> read(string fname);

};

#endif