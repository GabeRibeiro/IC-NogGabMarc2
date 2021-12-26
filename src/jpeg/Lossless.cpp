#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Lossless.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "../Golomb/Golomb.h"

using namespace std;
using namespace cv;


int Lossless::linear_jpeg_mode1(int a){return a;}
int Lossless::linear_jpeg_mode2(int b){return b;}
int Lossless::linear_jpeg_mode3(int c){return c;}
int Lossless::linear_jpeg_mode4(int a, int b, int c){return a+b-c;}
int Lossless::linear_jpeg_mode5(int a, int b, int c){return a+(b-c)/2;}
int Lossless::linear_jpeg_mode6(int a, int b, int c){return b+(a-c)/2;}
int Lossless::linear_jpeg_mode7(int a, int b){return (a+b)/2;}
int Lossless::non_linear_jpegls(int a, int b, int c){
    if(c >= max(a,b)) return min(a,b);
    else if(c <= min(a,b) ) return max(a,b);
    return a+b-c;
}

void Lossless::set_function(int f){
    if(f>=0 && f<=7) this->function = f;
}

void Lossless::yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v){
    int i, j, rw=y.rows, cl=y.cols;
    double y_, u_, v_, r, b;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            y_ = y.at<uchar>(i, j);
            u_ = u.at<uchar>(i/2, j/2);
            v_ = v.at<uchar>(i/2, j/2);

            r = rgb.at<Vec3b>(i, j)[0] = v_/0.877 + y_;
            b = rgb.at<Vec3b>(i, j)[2] = u_/0.492 + y_;
            rgb.at<Vec3b>(i, j)[1] = (y_ - 0.299*r - 0.114*b)/0.587;
        }
    }
}

void Lossless::rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v){
    int i,j, rw=rgb.rows, cl=rgb.cols;
    double r,g,b;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            r = rgb.at<Vec3b>(i, j)[0];
            g = rgb.at<Vec3b>(i, j)[1];
            b = rgb.at<Vec3b>(i, j)[2];

            y.at<uchar>(i, j) = 0.299*r + 0.587*g + 0.114*b;
            if(i%2==0 && j%2==0){
                u.at<uchar>(i/2, j/2) = -0.147*r - 0.289*g + 0.436*b;
                v.at<uchar>(i/2, j/2) = 0.615*r - 0.515*g - 0.100*b;
            }
        }
    }
}

vector<int> Lossless::predictive_coding(Mat& yuv){
    int i, j, rw=yuv.rows, cl=yuv.cols, x, px,a,b,c;
    vector<int> r;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            x = yuv.at<uchar>(i, j);
            a = j==0? 0 : yuv.at<uchar>(i, j-1);
            b = i==0? 0 : yuv.at<uchar>(i-1, j);
            c = j==0? 0 : yuv.at<uchar>(i-1, j-1);

            
            switch(this->function){
                case 0: px = non_linear_jpegls(a,b,c); break;
                case 1: px = linear_jpeg_mode1(a); break;
                case 2: px = linear_jpeg_mode2(b); break;
                case 3: px = linear_jpeg_mode3(c); break;
                case 4: px = linear_jpeg_mode4(a,b,c); break;
                case 5: px = linear_jpeg_mode5(a,b,c); break;
                case 6: px = linear_jpeg_mode6(a,b,c); break;
                case 7: px = linear_jpeg_mode7(a,b); break;
            }
            r.push_back(x-px);
        }
    }
    return r;
}
/*
void Lossless::encode(string fname, Mat& rgb){
    Mat y(rgb.size(), rgb.type());
    Mat u(rgb.rows/2, rgb.cols/2, rgb.type());
    Mat v(rgb.rows/2, rgb.cols/2, rgb.type());
    rgb2yuv(rgb, y, u, v);
    vector<int> y_ = predictive_coding(y);
    vector<int> u_ = predictive_coding(u);
    vector<int> v_ = predictive_coding(v);



    /* //media das diagonais
    int mean=0;
    for(int i=0; i< ; i++) mean += ;
    mean/=;
    golomb = new Golomb((int)ceil(-1/log2(mean/(mean+1))), fname);
    
    golomb = new Golomb(40);
    vector<int> header;
    header.push_back(golomb->get_m());
    header.push_back(rgb.rows);
    header.push_back(rgb.cols);
    header.push_back(function);
    golomb->writeHdr(header);
    golomb->write(y_);
    golomb->write(u_);
    golomb->write(v_);
}
*/

void Lossless::predictive_decoding(Mat& yuv, vector<int> yuv_){
    int i, j, rw=yuv.rows, cl=yuv.cols,r,px,a,b,c;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            r = yuv_[i*cl+j];
            a = j==0? 0 : yuv_[i*cl+(j-1)];
            b = i==0? 0 : yuv_[(i-1)*cl+j];
            c = j==0? 0 : yuv_[(i-1)*cl+(j-1)];

            switch(this->function){
                case 0: px = non_linear_jpegls(a,b,c); break;
                case 1: px = linear_jpeg_mode1(a); break;
                case 2: px = linear_jpeg_mode2(b); break;
                case 3: px = linear_jpeg_mode3(c); break;
                case 4: px = linear_jpeg_mode4(a,b,c); break;
                case 5: px = linear_jpeg_mode5(a,b,c); break;
                case 6: px = linear_jpeg_mode6(a,b,c); break;
                case 7: px = linear_jpeg_mode7(a,b); break;
            }
            yuv_[i*cl+j] = px;
            yuv.at<Vec3b>(i, j)[0] = px + r;
        }
    }
}

/*
void Lossless::decode(string fname, Mat&rgb){
    golomb = new Golomb(10, fname);
    vector<int> hdr = golomb->readHdr(3);
    int rows = hdr[0], cols = hdr[1];
    set_function(hdr[2]);

    vector<int> g_rd = golomb->read(3*rows*cols/2);
    
    Mat y(rows, cols, CV_8UC1);
    Mat u(rows/2, cols/2, CV_8UC1);
    Mat v(rows/2, cols/2, CV_8UC1);
    vector<int> y_(&g_rd[0], &g_rd[rows*cols-1]);
    vector<int> u_(&g_rd[rows*cols], &g_rd[5*rows*cols+rows/4-1]);
    vector<int> v_(&g_rd[5*rows*cols+rows/4], &g_rd[3*rows*cols/2-1]);

    predictive_decoding(y, y_);
    predictive_decoding(u, u_);
    predictive_decoding(v, v_);
    yuv2rgb(rgb, y, u, v);
}
*/