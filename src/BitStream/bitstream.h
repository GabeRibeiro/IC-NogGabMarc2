#ifndef H_BITSTREAM
#define H_BITSTREAM

#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>
#include <string>

using namespace std;
using std::fstream;

/**
    * @brief This class allows to read and write binary files
*/
class bitstream : public fstream {
    public:
    
        /**
        * @brief This class allows to read and write binary files
        * @param parameter-name description
        */
        bitstream(char *fname, ios_base::openmode mode) : fstream(fname, mode) {
            if (mode & std::ios::out) {
                pointer = 7;
                writeMode = true;
            } else if (mode & std::ios::in) {
                pointer = -1;
                writeMode = false;
            }
        };

        //~bitstream();
            /**
            * @brief This function allows writing a single bit in a byte
            * @param value is the value to write in a byte
            */
        void writeBit(uint8_t value);
            /**
            * @brief This function allows writing multiple bits in n bytes
            * @param value is the value to write in a byte
            * @param n is the number of bytes to write the "value"
            */
        void writeNBits(uint8_t value, uint n);
        void writeNBits2(uint32_t* value, uint n);
            /**
                * @brief This function allows reading a single bit from a byte
            */
        uint8_t readBit();
        //uint32_t readNBits(uint n);
            /**
                * @brief This function allows reading multiple bits from one or more bytes
                * @param n is the number of bits to read from file
                * @returns An array of characters that contains the read bits
            */
        char* readNBits(uint n);
        void readBit(uint8_t* val);
        //void readNBits2(uint32_t* value, uint n);
            /**
                * @brief This function allows adding zero's to fill the last byte written
            */
        void padding();
        string toString(char* c, int n);

    //private:
        u_char byte = 0;
        int pointer;
        int byteCount;
        bool writeMode;
};
#endif