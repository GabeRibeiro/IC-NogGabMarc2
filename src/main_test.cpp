#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "../src/Golomb/Golomb.h"
#include "../src/BitStream/bitstream.h"
#include "../src/jpeg/Lossless.h"
//#include "../jpeg/Lossy.h"

using namespace std;
using namespace cv;

int main(void){
    string filename = "testfile.bin";
    bitstream bss((char*) filename.data(), std::ios::binary|std::ios::out);
    bitstream bs((char*) filename.data(), std::ios::binary|std::ios::in);

    string s[5] = {"01011100", "01001", "110101", "0100111", "1100110"};
    for(int i=0; i<5; i++){
        for(int j=0; j<(int)s[i].size(); j++){
            bss.writeBit( (s[i][j]=='0'? 0 : 1) );
        }
    }
    bss.padding();
    bss.close();

    char *a;
    for(int j=0; j<31; j++){
        if(j!=0 && j%8==0) cout << endl;
        cout << (int)bs.readBit();
        if(j==5 || j==13 || j==21){
            cout << "\nread n bit: ";
            a = bs.readNBits(4);
            //cout << "size: " << sizeof(a)/2;
            for(int i=0; i<4; i++) cout << (int)(  (a[i/8] >> (7-i%8) ) & (0x01 ));
            cout << endl;
            j+=3;
        }
        
    }
    cout << endl;

    /*
    Golomb g(2);
    cout << g.signed_encode(-8) << endl;
    vector<int> v;
    v.push_back(4);
    v.push_back(7);
    g.write("marco.bin", v);
    g.read("marco.bin");*/
    return 0;
}
