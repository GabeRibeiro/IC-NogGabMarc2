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

int mat_u = 0;


/*


void yuv2rgb(Mat& rgb, Mat& y, Mat& u, Mat& v){
    int i, j, rw=y.rows, cl=y.cols;
    double y_, u_, v_, r, b;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            y_ = y.at<Vec3b>(i, j)[0];
            u_ = u.at<Vec3b>(i/2, j/2)[0];
            v_ = v.at<Vec3b>(i/2, j/2)[0];

            r = rgb.at<Vec3b>(i, j)[0] = v_/0.877 + y_;
            b = rgb.at<Vec3b>(i, j)[2] = u_/0.492 + y_;
            rgb.at<Vec3b>(i, j)[1] = (y_ - 0.299*r - 0.114*b)/0.587;
        }
    }
}

void rgb2yuv(Mat& rgb, Mat& y, Mat& u, Mat& v){
    int i,j,k, rw=rgb.rows, cl=rgb.cols;
    double r,g,b;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            r = rgb.at<Vec3b>(i, j)[0];
            g = rgb.at<Vec3b>(i, j)[1];
            b = rgb.at<Vec3b>(i, j)[2];

            y.at<Vec3b>(i, j) = 0.299*r + 0.587*g + 0.114*b;
            if(i%2==0 && j%2==0){
                u.at<Vec3b>(i/2, j/2) = -0.147*r - 0.289*g + 0.436*b;
                v.at<Vec3b>(i/2, j/2) = 0.615*r - 0.515*g - 0.100*b;
            }
        }
    }
}


vector<int> lossy_predictive_coding(Mat& yuv, int (*function)(int, int, int)){
    int i, j, rw=yuv.rows, cl=yuv.cols, x,px,a,b,c;
    vector<int> r;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            x = yuv.at<Vec3b>(i, j)[0];
            a = j==0? 0 : yuv.at<Vec3b>(i, j-1)[0];
            b = i==0? 0 : yuv.at<Vec3b>(i-1, j)[0];
            c = j==0? 0 : yuv.at<Vec3b>(i-1, j-1)[0];

            px = function(a,b,c);
            r.push_back((x-px) >> 1 << 1);
            yuv.at<Vec3b>(i, j)[0] = px;
        }
    }
    return r;
}


vector<int> predictive_coding(Mat& yuv, int (*function)(int, int, int)){
    int i, j, rw=yuv.rows, cl=yuv.cols, x,px,a,b,c;
    vector<int> r;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            x = yuv.at<Vec3b>(i, j)[0];
            a = j==0? 0 : yuv.at<Vec3b>(i, j-1)[0];
            b = i==0? 0 : yuv.at<Vec3b>(i-1, j)[0];
            c = j==0? 0 : yuv.at<Vec3b>(i-1, j-1)[0];

            px = function(a,b,c);
            r.push_back(x-px);
        }
    }
    return r;
}


void encode(string img, string fname, int (*function)(int, int, int)){
    Mat rgb = cv::imread(img);
    Mat y(rgb.size(), rgb.type());
    Mat u(rgb.rows/2, rgb.cols/2, rgb.type());
    Mat v(rgb.rows/2, rgb.cols/2, rgb.type());
    rgb2yuv(rgb, y, u, v);
    vector<int> y_ = predictive_coding(y, function);
    vector<int> u_ = predictive_coding(u, function);
    vector<int> v_ = predictive_coding(v, function);

    Golomb g(40);
    int i;
    for(i=0; i<u_.size(); i++)
        cout << g.signed_encode(u_[i]) << endl;
}


void lossy_predictive_decoding(Mat& yuv, vector<int> yuv_, int (*function)(int, int, int)){
    int i, j, rw=yuv.rows, cl=yuv.cols,r,px,a,b,c;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            r = yuv_[i*cl+j+1];
            a = j==0? 0 : yuv_[i*cl+(j-1)];
            b = i==0? 0 : yuv_[(i-1)*cl+j+1];
            c = j==0? 0 : yuv_[(i-1)*cl+(j-1)];

            px = function(a,b,c);
            yuv_[i*cl+j] = px;
            yuv.at<Vec3b>(i, j)[0] = px + r;
        }
    }
}


void predictive_decoding(Mat& yuv, vector<int> yuv_, int (*function)(int, int, int)){
    int i, j, rw=yuv.rows, cl=yuv.cols,r,px,a,b,c;
    for(i=0; i<rw; i++){
        for(j=0; j<cl; j++){
            r = yuv_[i*cl+j];
            a = j==0? 0 : yuv_[i*cl+(j-1)];
            b = i==0? 0 : yuv_[(i-1)*cl+j];
            c = j==0? 0 : yuv_[(i-1)*cl+(j-1)];

            px = function(a,b,c);
            yuv_[i*cl+j] = px;
            yuv.at<Vec3b>(i, j)[0] = px + r;
        }
    }
}


Mat decode(string fname, int (*function)(int, int, int)){
    Golomb g(40);
    vector<int> g_rd = g.read_code(fname);
    int rows = g_rd[0], cols = g_rd[1];
    //set_function(g_rd[2]);

    Mat y(rows, cols, CV_8UC1);
    Mat u(rows/2, cols/2, CV_8UC1);
    Mat v(rows/2, cols/2, CV_8UC1);
    vector<int> y_ = ;
    vector<int> u_ = ;
    vector<int> v_ = ;

    predictive_decoding(y, y_, function);
    predictive_decoding(u, u_, function);
    predictive_decoding(v, v_, function);
    Mat rgb(rows, cols, CV_8UC1);
    yuv2rgb(rgb, y, u, v);

    return rgb;
}
*/



int main(void){
    /* teste pre process
    cv::Mat r, y;
    r = cv::imread("lena.ppm");
    cv::imshow("original_rgb",r);
    y = Mat::zeros(r.size(), r.type());
    Mat u(r.rows/2, r.cols/2, r.type());
    Mat v(r.rows/2, r.cols/2, r.type());
    rgb2yuv(r, y, u, v);
    cv::imshow("y", y);
    
    cv::imshow("u", u);
    cv::imshow("v", v);

    mat_u=1;
    yuv2rgb(r, y, u ,v);
    mat_u=0;
    cv::imshow("new_rgb",r);

    cv::waitKey(0);
    */

    //encode("lena.ppm", "img_coded.txt", linear_jpeg_mode4);
    //decode("img_coded.txt", linear_jpeg_mode4);

    Golomb g(10);
    cout << g.signed_encode(12) <<endl;
    return 0;
}