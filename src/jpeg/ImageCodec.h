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
   * @brief Class for lossless ImageCodec
*/
class ImageCodec{
    public:
        int function=0, shift=0;
        /**
            * @brief Converts YUV 4:2:0 to RGB 
            * @param rgb matrix containing 3 channels RGB values 
            * @param y matrix containing Y channel values
            * @param u matrix containing U channel values
            * @param v matrix containing V channel values
        */
        void yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v);
        ///Dado imagem em RGB faz a conversão para YUV420
        /**
            * @brief Converts RGB to YUV 4:2:0
            * @param rgb matrix containing 3 channels RGB values
            * @param y matrix containing Y channel values
            * @param u matrix containing U channel values
            * @param v matrix containing V channel values
        */
        void rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v);
        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @param b top neighbor pixel
            * @param c top left neighbor pixel
            * @return predicted value
        */
        int non_linear_jpegls(int a, int b, int c);

        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode1(int a);
        /**
            * @brief Predict function
            * @param b top neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode2(int b);
        /**
            * @brief Predict function
            * @param c top left neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode3(int c);
        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @param b top neighbor pixel
            * @param c top left neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode4(int a, int b, int c);
        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @param b top neighbor pixel
            * @param c top left neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode5(int a, int b, int c);
        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @param b top neighbor pixel
            * @param c top left neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode6(int a, int b, int c);
        /**
            * @brief Predict function
            * @param a left neighbor pixel
            * @param b top neighbor pixel
            * @return predicted value
        */
        int linear_jpeg_mode7(int a, int b);
        /**
            * @brief Applies predictive functions to encode 1 channel YUV
            * @param yuv matrix containing a single channel YUV values
            * @return integer vector containing residuals
        */
        vector<int> predictive_coding(Mat& yuv);
        /**
            * @brief Applies predictive functions to decode 1 channel YUV
            * @param yuv matrix that will contain a single channel YUV values
            * @param yuv_ integer vector containing residuals
        */
        void predictive_decoding(Mat& yuv, vector<int> yuv_);

        /**
            * @brief Function to calculate entropy
            * @param vec integer vector containing channel values
            * @return entropy value
        */
        double entropy(vector<int> vec);

    //public:
        
        void set_shift(int s);

        void set_function(int f);
        /**
            * @brief Encodes an image and stores in a binary file
            * @param fname name of the file to store coded image
            * @param img Matrix containing image values to be encoded
        */
        void encode(string fname, Mat& img);
        /**
            * @brief Decodes an image stored in a binary file
            * @param fname name of the file with the coded image
            * @param img Matrix containing image values to be decoded
        */
        void decode(string fname, Mat& img);
};

#endif