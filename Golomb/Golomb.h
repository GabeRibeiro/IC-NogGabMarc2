#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
using namespace std;

class Golomb{
    private:
        int m;
        int b;
        string unary(int q);
        string binary(int x, int n);
        int decimal(string a);

    public:
        Golomb(int m);
        string encode(signed int n);
        int decode(string str);
        string  signed_encode(int n);
        int signed_decode(string code);
        void set_m(int m);
        int get_m(void);   
};