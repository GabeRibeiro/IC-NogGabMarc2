#include "AudioCodec.h"
#include <stdio.h>
#include <sndfile.h>
#include "../BitStream/bitstream.h"
#include "../Golomb/Golomb.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


void AudioCodec::set_order(int o){
    this->order = o;
}

void AudioCodec::set_shift(int s){
    this->shift = s;
}

double AudioCodec::entropy(vector<int> vec){
    unordered_map<int, double> ch;
    double entropy_ch=0, prob;
    int total = vec.size(), value;

    for(int i : vec){    
        value = i;
        ch[i]++;
    }

    for(auto it:ch) {
        prob = double (it.second / double(total));
        entropy_ch += prob * log2(prob);
    }
    return -entropy_ch; 
}

vector<short> AudioCodec::predictive_coding(vector<short> aud){
    cout << "Encoding" << endl;
    vector<short> rsd, prdt;
    int px, x1=0, x2=0, x3=0, r;
    for(int i =0; i<(int)aud.size(); i++){
        switch(order){
            case 1: px = x1; break;
            case 2: px = 2*x1 - x2; break;
            case 3: px = 3*x1 - 3*x2 + x3; break;
        }
		r = ((aud[i]-px) >> shift )<< shift;
        prdt.push_back(px);
        rsd.push_back(r);
        x3=x2;
        x2=x1;
        aud[i] = r + px;
        x1=aud[i];
    }
    return rsd;
}

void AudioCodec::encode(string fname, char const* wav){
    SNDFILE *snd;
    SF_INFO sfinfo;
    memset (&sfinfo, 0, sizeof (sfinfo));

    if(!(snd = sf_open(wav, SFM_READ, &sfinfo)))
        throw runtime_error("Error opening sound file.");

    short cnt, cls[sfinfo.channels];
    vector<short> vcnl[sfinfo.channels], rcnl[sfinfo.channels];

    while((cnt = (int) sf_readf_short(snd, cls, 1))>0){
        for(int i=0; i<sfinfo.channels; i++)
            vcnl[i].push_back(cls[i]);
    }

    for(int i=0; i<sfinfo.channels; i++)
        rcnl[i] = predictive_coding(vcnl[i]);
    
    vector<int> map;
    for(int i=0; i<sfinfo.channels; i++)
        transform(rcnl[i].begin(), rcnl[i].end(), back_inserter(map),  
        [](int x) { return  x>=0? x * 2 : -2*x-1; });  
    double mean=accumulate(map.begin(), map.end(), 0);
    Golomb gb(  ceil(-1/log2(mean/(mean+1)))  );
    
    cout << "Golomb m: " << gb.get_m() << endl;

    bitstream bss((char*) fname.data(), std::ios::binary|std::ios::out);
    
    vector<int> hdr;
    hdr.push_back(gb.get_m());          //m de golomb
    hdr.push_back(sfinfo.channels);     //numero de canais
    hdr.push_back(sfinfo.frames);       //numero de samples
    hdr.push_back(sfinfo.format);       //formato
    hdr.push_back(sfinfo.samplerate);   //samplerate
    hdr.push_back(order);               //ordem
    cout << "writing header" << endl;
    gb.writeHdr(hdr, bss);


    cout << "writing wav" << endl;
    for(int i=0; i<sfinfo.channels; i++)
        gb.write(rcnl[i], bss);
    bss.padding();

    sf_close(snd);
}

vector<short> AudioCodec::predictive_decoding(vector<short> rsd){
    cout << "Decoding" << endl;
    int px, x1=0, x2=0, x3=0;
    vector<int> v;
    for(int i =0; i<(int)rsd.size(); i++){
        switch(order){
            case 1: px = x1; break;
            case 2: px = 2*x1 - x2; break;
            case 3: px = 3*x1 - 3*x2 + x3; break;
        }
		v.push_back(px+rsd[i]);
        x3=x2;
        x2=x1;
        x1=v[i];
    }
    return v;
}

void AudioCodec::decode(string fname, char const* wav){
    bitstream bss((char*) fname.data(), std::ios::binary|std::ios::in);
    Golomb gb(10);
    cout << "Reading header" << endl;
    vector<int> hdr = gb.readHdr(6, bss);
    gb.set_m(hdr[0]);
    order = hdr[5];

    SF_INFO sfinfo ;
    sfinfo.channels = hdr[1];
    sfinfo.format = hdr[3];
    sfinfo.samplerate = hdr[4];

    vector<int> rcnl[hdr[1]], vcnl[hdr[1]];
    for(int i=0; i<hdr[1]; i++){
        rcnl[i] = gb.read(hdr[2], bss);
        vcnl[i] = predictive_decoding(rcnl[i]);
    }

    
    vector<int> wrt;
    for(int i=0; i<(int)vcnl[0].size(); i++){
        for(int j=0; j<sfinfo.channels; j++)
            wrt.push_back(vcnl[j][i]);
    }

    cout << "Reading wav" << endl;
    SNDFILE * outfile = sf_open(wav, SFM_WRITE, &sfinfo);
    sf_count_t count = sf_write_int(outfile, &wrt[0], (int)vcnl[0].size()) ;
    sf_write_sync(outfile);
    sf_close(outfile);
}
