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

        vector<short> predictive_coding(vector<short> aud);

        vector<short> predictive_decoding(vector<short> rsd);

        double entropy(vector<int> vec);
    //public:

        void set_order(int o);

        void set_shift(int s);

        void encode(string fname, char const* wav);

        void decode(string fname, char const* wav);
};


#endif