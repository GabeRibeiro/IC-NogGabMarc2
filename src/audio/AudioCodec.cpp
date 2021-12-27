#include "AudioCodec.h"
#include <stdio.h>
#include <sndfile.h>
#include "../BitStream/bitstream.h"
#include "../Golomb/Golomb.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>
#include <cmath>
#include <math.h>
#include <vector>
using namespace std;

vector<int> AudioCodec::predictive_coding(vector<int> aud){
    vector<int> prd;
    int px, x1=0, x2=0, x3=0;
    for(int i =0; i<(int)aud.size(); i++){
        switch(order){
            case 1: px = x1; break;
            case 2: px = 2*x1 - x2; break;
            case 3: px = 3*x1 - 3*x2 + x3; break;
        }

        prd.push_back(aud[i]-px);
        x3=x2;
        x2=x1;
        x1=aud[i];
    }
    return prd;
}

void AudioCodec::encode(const char* fname){
    SNDFILE *snd;
    SF_INFO info;
    memset (&info, 0, sizeof (info));

    if(!(snd = sf_open(fname, SFM_READ, &info)))
        throw runtime_error("Error opening sound file.");
    int cnt, cls[info.channels];
    vector<int> vcnl[info.channels], rcnl[info.channels];
    while((cnt = (int) sf_readf_int(snd, cls, 1))>0){
        for(int i=0; i<info.channels; i++)
            vcnl[i].push_back(cls[i]);
    }

    for(int i=0; i<info.channels; i++)
        rcnl[i] = predictive_coding(vcnl[i]);

    /*
    bitstream b();
    Golomg glb();
    vector<int> hdr;
    hdr.push_back(glb.get_m()); //m de golomb
    hdr.push_back();    //numero de canais
    hdr.push_back();    //numero de samples
    hdr.push_back();
    glb.writeHdr(hdr. b);

    for(int i=0; i<info.channels; i++)
        glb.write(rcnl[i], b);
    */

    sf_close(snd);
}

void AudioCodec::predictive_decoding(vector<int> prc){

}

void AudioCodec::decode(const char* fname){
    /*
    bitstream b();
    Golomg glb(10);
    vector<int> hdr = glb.read

    */
}
