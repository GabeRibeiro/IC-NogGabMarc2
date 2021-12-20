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
    Golomb g(2);
    cout << g.signed_encode(-8) << endl;
    vector<int> v;
    v.push_back(4);
    v.push_back(7);
    g.write("marco.bin", v);
    g.read("marco.bin");
    return 0;
}
