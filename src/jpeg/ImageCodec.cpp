#include <iomanip>
#include <algorithm>
#include <numeric>  
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "ImageCodec.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "../Golomb/Golomb.h"

using namespace std;
using namespace cv;


int ImageCodec::linear_jpeg_mode1(int a){return a;}
int ImageCodec::linear_jpeg_mode2(int b){return b;}
int ImageCodec::linear_jpeg_mode3(int c){return c;}
int ImageCodec::linear_jpeg_mode4(int a, int b, int c){return a+b-c;}
int ImageCodec::linear_jpeg_mode5(int a, int b, int c){return a+(b-c)/2;}
int ImageCodec::linear_jpeg_mode6(int a, int b, int c){return b+(a-c)/2;}
int ImageCodec::linear_jpeg_mode7(int a, int b){return (a+b)/2;}
int ImageCodec::non_linear_jpegls(int a, int b, int c){
    if(c >= max(a,b)) return min(a,b);
    else if(c <= min(a,b) ) return max(a,b);
    return a+b-c;
}

void ImageCodec::set_function(int f){
    if(f>=0 && f<=7) this->function = f;
}

void ImageCodec::set_shift(int s){
    this->shift = s;
}

void ImageCodec::yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v){
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

void ImageCodec::rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v){
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

vector<int> ImageCodec::predictive_coding(Mat& yuv){
    int rw=yuv.rows, cl=yuv.cols, x, px,a,b,c, rsd;
    vector<int> r;
    cout<< "Encoding "<< endl;
    for(int i=0; i<rw; i++){
        for(int j=0; j<cl; j++){
            x = yuv.at<uchar>(i, j);
            a = j==0? 0 : yuv.at<uchar>(i, j-1);
            b = i==0? 0 : yuv.at<uchar>(i-1, j);
            c = j==0 || i==0? 0 : yuv.at<uchar>(i-1, j-1);

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
            rsd = ((x-px) >> shift) << shift;
            r.push_back(rsd);
            yuv.at<uchar>(i, j) = rsd + px;
        }
    }
    return r;
}

void ImageCodec::encode(string fname, Mat& rgb){
    Mat y(rgb.size(), CV_8UC1);
    Mat u(rgb.rows/2, rgb.cols/2, CV_8UC1);
    Mat v(rgb.rows/2, rgb.cols/2, CV_8UC1);
    rgb2yuv(rgb, y, u, v);
    cv::imshow("y", y);
    cv::imshow("u", u);
    cv::imshow("v", v);
    
    vector<int> y_ = predictive_coding(y);
    vector<int> u_ = predictive_coding(u);
    vector<int> v_ = predictive_coding(v);
    
    vector<int> map;
    transform(y_.begin(), y_.end(), back_inserter(map),  
    [](int x) { return  x>=0? x * 2 : -2*x-1; });  
    transform(u_.begin(), u_.end(), back_inserter(map),  
    [](int x) { return  x>=0? x * 2 : -2*x-1; });
    transform(v_.begin(), v_.end(), back_inserter(map),  
    [](int x) { return  x>=0? x * 2 : -2*x-1; });
    double mean=accumulate(map.begin(), map.end(), 0);
    mean/= 3*rgb.rows*rgb.cols/2 ;
    Golomb gb(  ceil(-1/log2(mean/(mean+1)))  );
    bitstream bss((char*) fname.data(), std::ios::binary|std::ios::out);

    vector<int> header;
    header.push_back(gb.get_m()); //m de golomb
    header.push_back(rgb.rows); //n rows
    header.push_back(rgb.cols); //n de cols
    header.push_back(function); //predict function usada
    cout << "write header" << endl;
    gb.writeHdr(header, bss);

    cout << "Write yuv" << endl;
    gb.write(y_, bss);
    gb.write(u_, bss);
    gb.write(v_, bss);
    bss.padding();
    bss.close();
}

void ImageCodec::predictive_decoding(Mat& yuv, vector<int> yuv_){
    int rw=yuv.rows, cl=yuv.cols,r,px,a,b,c;
    cout<< " Decoding "<< endl;
    for(int i=0; i<rw; i++){
        for(int j=0; j<cl; j++){
            r = yuv_[i*cl+j];
            a = j==0? 0 : yuv.at<uchar>(i, j-1);
            b = i==0? 0 : yuv.at<uchar>(i-1, j);
            c = j==0 || i==0? 0 : yuv.at<uchar>(i-1, j-1);

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
            yuv.at<uchar>(i, j) = px+r;
        }
    }
}

void ImageCodec::decode(string fname, Mat&rgb){
    bitstream bss((char*) fname.data(), std::ios::binary|std::ios::in);
    Golomb gb(11);
    vector<int> hdr = gb.readHdr(4, bss);
    gb.set_m(hdr[0]);
    int rows = hdr[1], cols = hdr[2];
    set_function(hdr[3]);
    cout << "Read header" << endl;

    vector<int> g_rd = gb.read(3*rows*cols/2, bss);

    Mat y = Mat::zeros(rows, cols, CV_8UC1);
    Mat u = Mat::zeros(rows/2, cols/2, CV_8UC1);
    Mat v = Mat::zeros(rows/2, cols/2, CV_8UC1);

    cout << "Read yuv" << endl;
    vector<int> y_(&g_rd[0], &g_rd[rows*cols-1]);
    vector<int> u_(&g_rd[rows*cols], &g_rd[5*rows*cols/4-1]);
    vector<int> v_(&g_rd[5*rows*cols/4], &g_rd[3*rows*cols/2-1]);

    predictive_decoding(y, y_);
    predictive_decoding(u, u_);
    predictive_decoding(v, v_);

    cv::imshow("new y", y);
    cv::imshow("new u", u);
    cv::imshow("new v", v);
    yuv2rgb(rgb, y, u, v);

    bss.close();
}
