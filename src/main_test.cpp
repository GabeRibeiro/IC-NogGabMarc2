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
    /*
    ImageCodec i;
    i.set_shift(0);
    Mat img = cv::imread("lena.ppm");
    i.encode("testfile.bin", img);
    i.decode("testfile.bin", img);
    cv::imshow("new rgb", img);
    cv::waitKey(0);*/

    
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
        cout << "Nome do ficheiro imagem a escrever: " << endl;
        cin >> rgb;
        img.decode(filename, mat);
        cv::imwrite(rgb, mat);
        cv::imshow("new rgb", mat);
        cv::waitKey(0);
        cout << "Fim de processo de descodificaçao." << endl;
    }
   return 0;
}
