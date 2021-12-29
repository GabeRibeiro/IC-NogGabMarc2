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
        /**
            * @brief Encodes an audio file based on predictive functions
            * @param aud integer vector containing audio file values
            * @return integer vector with encoded values
        */
        vector<int> predictive_coding(vector<int> aud);
        /**
            * @brief Decodes an audio file based on predictive functions
            * @param rsd integer vector containing audio file values
            * @return integer vector with decoded values
        */
        vector<int> predictive_decoding(vector<int> rsd);
        /**
            * @brief Function to calculate entropy
            * @param vec integer vector containing sample values
            * @return entropy value
        */
        double entropy(vector<int> vec);
    //public:

        void set_order(int o);

        void set_shift(int s);
        /**
            * @brief Encodes an audio file and stores in a binary file
            * @param fname name of the file to store coded audio file
            * @param wav name of the audio file
        */
        void encode(string fname, char const* wav);
        /**
            * @brief Decodes an audio file stored in a binary file
            * @param fname name of the file containing coded audio file
            * @param wav name of the audio file
        */
        void decode(string fname, char const* wav);
};


#endif