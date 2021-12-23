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

    /*
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
        if(j==5){
            cout << "\nread n bit: ";
            a = bs.readNBits(10);
            //cout << "size: " << sizeof(a)/2;
            //for(int i=0; i<10; i++) cout << (int)(  (a[i/8] >> (7-i%8) ) & (0x01 ));
            cout << bs.toString(a, 10) << endl;
            cout << endl;
            j+=9;
        }
        
    }
    cout << endl;
    */


    /*
    Lossless ls;
    Mat rgb = cv::imread("lena.ppm");
    cv::imshow("original rgb",rgb);
    Mat y(rgb.size(), CV_8UC1);
    Mat u(rgb.rows/2, rgb.cols/2, CV_8UC1);
    Mat v(rgb.rows/2, rgb.cols/2, CV_8UC1);
    ls.rgb2yuv(rgb, y, u, v);
    cv::imshow("y", y);
    cv::imshow("u", u);
    cv::imshow("v", v);
    ls.yuv2rgb(rgb, y, u, v);
    cv::imshow("new rgb", rgb);
    cv::waitKey(0);
    */


   Golomb g(5);
   vector<int> v, h;
   v.push_back(15);
   v.push_back(5);
   v.push_back(12);
   v.push_back(21);
   cout << g.binary(4,16) << endl;
   cout << g.binary(5,16) << endl;
   for(int i =0; i<(int)v.size(); i++) cout << g.signed_encode(v[i]) <<endl;
   g.write("testfile.bin", v);

   h = g.read("testfile.bin");
   for(int i =0; i<(int)h.size(); i++) cout << h[i] <<endl; 
   return 0;
}
