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

    
    //teste audio encode e decode

    AudioCodec aud;
    char* wav;
    string filename;
    int i;
    char yn;

    cout << "Pretende codificar um ficheiro audio?[y/n]" << endl;
    cin >> yn;
    if(yn == 'y'){
        cout << "Nome do ficheiro audio a ler: " << endl;
        cin >> wav;
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
        cout << "Nome do ficheiro audio a escrever: " << endl;
        cin >> wav;
        aud.decode(filename, wav);
        cout << "Fim de processo de descodificaçao." << endl;
    }

   return 0;
}