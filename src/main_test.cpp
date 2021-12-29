#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "../src/audio/AudioCodec.h"
#include "../src/Golomb/Golomb.h"
#include "../src/BitStream/bitstream.h"
#include "../src/jpeg/ImageCodec.h"


using namespace std;
using namespace cv;

int main(void){
    /* teste bitstream
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


    /* teste rgb yuv
    ImageCodec ls;
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

   /* teste golomb
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
   */


   //teste escrever e ler no ficheiro
   /*
   Golomb g(5);
   string filename = "testfile.bin";
   bitstream bss((char*) filename.data(), std::ios::binary|std::ios::out);
   bitstream bs((char*) filename.data(), std::ios::binary|std::ios::in);

   vector<int> h = {5, 3, 2, 8};
   g.writeHdr(h, bss);
   vector<int> v1 = {12, 1, 4};
   vector<int> v2 = {32, 21, 6};
   g.write(v1, bss);
   g.write(v2, bss);
   bss.padding();
   bss.close();
   

   Golomb gb(10);
   vector<int> h_ = gb.readHdr(4, bs);
   cout << "header linha: " << endl;
   for(int i=0; i<(int)h_.size(); i++) cout << h_[i] << endl;
   gb.set_m(h_[0]);
   vector<int> v_ = gb.read(6, bs);
   cout << "vector: " << endl;
   for(int i=0; i<(int)v_.size(); i++) cout << v_[i] << endl; 
   bs.close();
   */

    /*
    //teste img encode e decode
    ImageCodec i;
    i.set_shift(7);
    Mat img = cv::imread("lena.ppm");
    i.encode("testfile.bin", img);
    i.decode("testfile.bin", img);
    cv::imshow("new rgb", img);
    cv::waitKey(0);
    */

    ImageCodec img;
    Mat mat;
    string filename, rgb;
    int i;
    char yn;

    cout << "Pretende codificar um ficheiro imagem?[y/n]" << endl;
    cin >> yn;
    if(yn == 'y'){
        cout << "Nome do ficheiro imagem a ler: " << endl;
        cin >> rgb;
        mat = cv::imread(rgb);
        cout << "Nome do ficheiro binario a escrever: " << endl;
        cin >> filename;
        cout << "Qual predict function usar: [0 a 7]" << endl;
        cin >> i;
        img.set_function(i);
        cout << "Nivel de quantização : [0 a 7]" << endl;
        cin >> i;
        img.set_shift(i);
        img.encode(filename, mat);
        cout << "Fim de processo de codificaçao." << endl;
    }
    
    cout << "Pretende descodificar um ficheiro audio?[y/n]" << endl;
    cin >> yn;
    if(yn == 'y'){
        cout << "Nome do ficheiro binario a ler: " << endl;
        cin >> filename;
        cout << "Nome do ficheiro audio a escrever: " << endl;
        cin >> rgb;
        mat = cv::imread(rgb);
        img.decode(filename, mat);
        cv::imshow("new rgb", mat);
        cv::imwrite(filename, mat);
        cv::waitKey(0);
        cout << "Fim de processo de descodificaçao." << endl;
    }

   return 0;
}
