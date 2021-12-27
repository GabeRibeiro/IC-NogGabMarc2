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

/**
 * @file Lossless.cpp
 * Class for lossless image codec
 */
class ImageCodec{
    public:
        int function = 0;
        /**
         * Dados 3 canais  faz a conversão para RGB
         */
        void yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v);
        ///Dado imagem em RGB faz a conversão para YUV420
        void rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v);

        int non_linear_jpegls(int a, int b, int c);

        int linear_jpeg_mode1(int a);

        int linear_jpeg_mode2(int b);

        int linear_jpeg_mode3(int c);

        int linear_jpeg_mode4(int a, int b, int c);

        int linear_jpeg_mode5(int a, int b, int c);

        int linear_jpeg_mode6(int a, int b, int c);

        int linear_jpeg_mode7(int a, int b);

        vector<int> predictive_coding(Mat& yuv);

        void predictive_decoding(Mat& yuv, vector<int> yuv_);
    //public:
        
        void set_function(int f);

        void encode(string fname, Mat& img);

        void decode(string fname, Mat& img);
};

#endif