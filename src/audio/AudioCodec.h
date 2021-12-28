#ifndef H_AUDIU_LOSSLESS
#define H_AUDIO_LOSSLESS

#include <stdio.h>
#include <sndfile.h>
#include <vector>
#include "../BitStream/bitstream.h"
#include "../Golomb/Golomb.h"

class AudioCodec{
    public:
        
        int order = 1, shift =0;

        vector<int> predictive_coding(vector<int> aud);

        vector<int> predictive_decoding(vector<int> rsd);

        void entropy(vector<int> aud);
    //public:

        void set_order(int o);

        void set_shift(int s);

        void encode(string fname, char const* wav);

        void decode(string fname, char const* wav);
};


#endif