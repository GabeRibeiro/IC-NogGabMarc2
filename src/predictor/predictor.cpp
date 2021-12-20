#include "predictor.h"
using namespace std;

void predictor::printCircleBuffer(){
    cout << "pointer:\t" << ptr << endl;
    cout << circularBuffer[0] << ", " << circularBuffer[1] << ", " << circularBuffer[2] << endl;
}

int predictor::predict()
{   switch(ninputs) {
        case 0:
            return 0;
        case 1:
            return circularBuffer[ptr];
        case 2:
            return (2 * (circularBuffer[ptr]) - (circularBuffer[(ptr+2)%3]));
        default:
            return (3 * ( circularBuffer[ptr]) - 3 * (circularBuffer[(ptr+2) % 3]) +
                            (circularBuffer[(ptr+1) % 3]));
    }
}

int predictor::residual(int sample)
{   int pred = predict();
    if(!lossy) 
    {
        updateBuffer(sample);
    }
    return sample - pred;
}

void predictor::updateBufQuant(int quant){
    updateBuffer(predict()+quant);
}

void predictor::updateBuffer(int sample) {
    ptr = ((ptr + 1) % 3);
    circularBuffer[ptr] = sample;
    if(ninputs < order) ninputs++;
}

int predictor::reconstruct(int residual)
{   
    int rec = (predict() + residual);
    updateBuffer(rec);
    return rec;
}
