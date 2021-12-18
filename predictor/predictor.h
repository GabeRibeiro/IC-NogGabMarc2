#ifndef PREDICTOR_H
#define PREDICTOR_H
#include <iostream>

using namespace std;

class predictor{

    public:

        int predict();
        void printCircleBuffer();
        int reconstruct(int residual);
        int residual(int sample);
        void updateBufQuant(int quant);
        

        predictor(bool l,int ord){
            lossy = l;
            order = ord;
            ninputs = 0;
            ptr = 2;
        }

    private:
        void updateBuffer(int sample);
        int order;
        bool lossy;
        int ninputs;
        int lossy;
        int circularBuffer[3] = {0,0,0};
        int ptr;
};

#endif 