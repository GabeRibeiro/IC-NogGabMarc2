#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>

#include "../src/audio/AudioCodec.cpp"
#include "../src/Golomb/Golomb.cpp"
#include "../src/BitStream/bitstream.cpp"


using namespace std;

int main(void){
    
   /*
    //teste audio library
    char const* wav = "sample01.wav";
    SNDFILE *snd;
    SF_INFO sfinfo;
    memset (&sfinfo, 0, sizeof (sfinfo));

    if(!(snd = sf_open(wav, SFM_READ, &sfinfo)))
        throw runtime_error("Error opening sound file.");

    int cnt, cls[sfinfo.channels];
    vector<int> vcnl[sfinfo.channels];
    while((cnt = (int) sf_readf_int(snd, cls, 1))>0){
        for(int i=0; i<sfinfo.channels; i++)
            vcnl[i].push_back(cls[i]);
    }

    cout << "audio file info\n" << "channels  " << sfinfo.channels << endl;
    cout << "sample rate  " << sfinfo.samplerate << endl;
    cout << "nº de samples  " << sfinfo.frames << endl;
    cout << "size channel " << (int)vcnl[0].size() << endl;
    cout << "formato  " << sfinfo.format << endl;


    char const* wav2 = "smp1.wav";
    SNDFILE * outfile = sf_open(wav2, SFM_WRITE, &sfinfo);

    vector<int> wrt;
    for(int i=0; i<(int)vcnl[0].size(); i++){
        for(int j=0; j<sfinfo.channels; j++)
            wrt.push_back(vcnl[j][i]);
    }
        
    sf_count_t count = sf_write_int(outfile, &wrt[0], (int)vcnl[0].size()) ;
    sf_write_sync(outfile);
    sf_close(outfile);
    */

    
    //teste audio encode e decode
    AudioCodec aud;
    char const* wav = "sample01.wav";
    char const* wav2 = "new_smp01.wav";
    aud.encode("testfile.bin", wav);
    aud.decode("testfile.bin", wav2);



   return 0;
}