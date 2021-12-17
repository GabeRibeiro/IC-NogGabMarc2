#ifndef H_BITSTREAM
#define H_BITSTREAM

#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>

using std::fstream;


class bitstream : public fstream {
    public:
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
        void writeBit(uint8_t value);
        void writeNBits(uint8_t value, uint n);
        void writeNBits2(uint32_t* value, uint n);
        uint8_t readBit();
        //uint32_t readNBits(uint n);
        char* readNBits(uint n);
        void readBit(uint8_t* val);
        //void readNBits2(uint32_t* value, uint n);
        //void addWhiteSpace();

    private:
        u_char byte = 0;
        int pointer;
        int byteCount;
        bool writeMode;
};
#endif