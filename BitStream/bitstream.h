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


    //  bit_stream(char *fname){
    //         pointer_read = -1;
    //         pointer_write = 7;
    //         pointer = 7;
    //         filename = fname;
    //         byteCount = 0;
    //         inputfile = ifstream(fname, ios::binary);
    //         outputfile = ofstream(fname, ios::binary);
    //         byte = '0';
    //         //inputfile.open(fname, fstream::in);
    //         //outputfile.open(fname, fstream::out);

    //     };

        //~bitstream();
        void writeBit(u_char value);
        void writeNBits(u_char value, uint n);
        void writeNBits(u_char* value, uint n);
        u_char readBit();
        u_char readNBits(uint n);
        void readNBits(u_char* value, uint n);
        //void addWhiteSpace();

    private:
        u_char byte = 0;
        int pointer;
        int byteCount;
        bool writeMode;
};
#endif