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

    AudioCodec aud;
    char const* wav = "sample01.wav"; //por se tratar de const tem de ser alterado aqui
    string filename;
    int i, w;
    char yn;

    cout << "Pretende codificar um ficheiro audio?[y/n]" << endl;
    cin >> yn;
    if(yn == 'y'){
        cout << "Nome do ficheiro binario a escrever: " << endl;
        cin >> filename;
        cout << "Qual ordem do predict function: [1 a 3]" << endl;
        cin >> i;
        aud.set_order(i);
        cout << "Nivel de quantização : [0 a 15]" << endl;
        cin >> i;
        aud.set_shift(i);
        aud.encode(filename, wav);
        cout << "Fim de processo de codificaçao." << endl;
    }
    
    cout << "Pretende descodificar um ficheiro audio?[y/n]" << endl;
    cin >> yn;
    if(yn == 'y'){
        cout << "Nome do ficheiro binario a ler: " << endl;
        cin >> filename;
        char const* res = "audio.wav";
        aud.decode(filename, res);
        cout << "Fim de processo de descodificaçao." << endl;
    }

   return 0;
}