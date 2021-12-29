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

        /**
            * @brief Constructor of Class Golomb
            * @param m 
        */
        Golomb(int m);
        /**
            * @brief The encode function allows encoding a number with the golomb coding algorithm
            * @param n is the number to encode
            * @returns string containing the golomb code
        */
        string encode(signed int n);
        /**
            * @brief The decode function allows decoding the golomb code
            * @param str containing the golomb code
            * @return number decoded from the golomb code
        */
        int decode(string str);
        /**
            * @brief The encode function allows encoding a signed number with the golomb coding algorithm
            * @param n is the number to encode
            * @returns string containing the golomb code
        */
        string  signed_encode(int n);
        /**
            * @brief The decode function allows decoding the golomb code
            * @param str containing the golomb code
            * @return signed number decoded from the golomb code
        */
        int signed_decode(string code);
        /**
            * @brief Function to set m value
            * @param m 
        */
        void set_m(int m);
        /**
            * @brief Function to get m value
            * @returns value of m
        */
        int get_m(void);
        /**
            * @brief Function to write in a vector v using bitstream
            * @param v is an integer vector
            * @param b is a bitstream address
        */
        void write(vector<int> v, bitstream &b);
        /**
            * @brief Function to read 'elems' bits using bitstream
            * @param elems is the number of bits to read
            * @param b is a bitstream address
            * @returns integer vector containing read values
        */
        vector<int> read(int elems, bitstream &b);
        /**
            * @brief Function to write Header in binary
            * @param v is an array of integers containing ... 
            * @param b is a bitstream address
        */
        void writeHdr( vector<int> v, bitstream &b);
        /**
            * @brief Function to read Header 
            * @param type is an integer that defines the type (specify content ...)
            * @param b is a bitstream address
            * @returns integer vector containing the Header information
        */
        vector<int> readHdr(int type, bitstream &b);

};

#endif