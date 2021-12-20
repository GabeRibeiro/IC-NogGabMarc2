#ifndef LOSSLESS_H
#define LOSSLESS_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "../Golomb/Golomb.h"

using namespace std;
using namespace cv;

class Lossless{
    private:
        
        Golomb *golomb;
        int function;
        void yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v);
        void rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v);
        int non_linear_jpegls(int a, int b, int c);
        int linear_jpeg_mode1(int a, int b, int c);
        int linear_jpeg_mode2(int a, int b, int c);
        int linear_jpeg_mode3(int a, int b, int c);
        int linear_jpeg_mode4(int a, int b, int c);
        int linear_jpeg_mode5(int a, int b, int c);
        int linear_jpeg_mode6(int a, int b, int c);
        int linear_jpeg_mode7(int a, int b, int c);
        vector<int> predictive_coding(Mat& yuv);
        //void predictive_decoding(Mat& yuv, vector<int> yuv_);
    public:
        void set_function(int f);
        void encode(string img, string fname);
        //Mat decode(string fname);
};

#endif