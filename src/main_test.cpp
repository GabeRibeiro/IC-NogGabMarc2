#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
//#include "../src/Golomb/Golomb.h"
//#include "../src/BitStream/bitstream.h"
#include "../src/jpeg/ImageCodec.h"
//#include "../src/audio/AudioCodec.h"
#include "../src/audio/AudioCodec.cpp"
#include "../src/Golomb/Golomb.cpp"
#include "../src/BitStream/bitstream.cpp"


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
    i.set_shift(0);
    Mat img = cv::imread("lena.ppm");
    i.encode("testfile.bin", img);
    i.decode("testfile.bin", img);
    cv::imshow("new rgb", img);
    cv::waitKey(0);
    */

   /*
    //teste audio library
    char const* wav = "sample01.wav";
    SNDFILE *snd;
    SF_INFO sfinfo;
    memset (&sfinfo, 0, sizeof (sfinfo));

    if(!(snd = sf_open(wav, SFM_READ, &sfinfo)))
        throw runtime_error("Error opening sound file.");

    int cnt, cls[sfinfo.channels];
    vector<int> vcnl[sfinfo.channels];
    while((cnt = (int) sf_readf_int(snd, cls, 1))>0){
        for(int i=0; i<sfinfo.channels; i++)
            vcnl[i].push_back(cls[i]);
    }

    cout << "audio file info\n" << "channels  " << sfinfo.channels << endl;
    cout << "sample rate  " << sfinfo.samplerate << endl;
    cout << "nº de samples  " << sfinfo.frames << endl;
    cout << "size channel " << (int)vcnl[0].size() << endl;
    cout << "formato  " << sfinfo.format << endl;


    char const* wav2 = "smp1.wav";
    SNDFILE * outfile = sf_open(wav2, SFM_WRITE, &sfinfo);

    vector<int> wrt;
    for(int i=0; i<(int)vcnl[0].size(); i++){
        for(int j=0; j<sfinfo.channels; j++)
            wrt.push_back(vcnl[j][i]);
    }
        
    sf_count_t count = sf_write_int(outfile, &wrt[0], (int)vcnl[0].size()) ;
    sf_write_sync(outfile);
    sf_close(outfile);
    */

    
    //teste audio encode e decode
    AudioCodec aud;
    char const* wav = "sample01.wav";
    char const* wav2 = "new_smp01.wav";
    aud.encode("testfile.bin", wav);
    aud.decode("testfile.bin", wav2);

    



   return 0;
}
