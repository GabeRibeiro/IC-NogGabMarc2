#ifndef H_AUDIU_LOSSLESS
#define H_AUDIO_LOSSLESS

#include <stdio.h>
#include <sndfile.h>
#include <vector>
#include "../BitStream/bitstream.h"
#include "../Golomb/Golomb.h"

class AudioCodec{
    public:
        /// indica a ordem do temporal do predictor
        int order = 1;

        vector<int> predictive_coding(vector<int> aud);

        void predictive_decoding(vector<int> prc);
    //public:

        void encode(const char* fname);

        void decode(const char* fname);
};


#endif