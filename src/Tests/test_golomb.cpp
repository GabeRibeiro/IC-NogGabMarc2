#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>

#include "../Golomb/Golomb.h"

using namespace std;

int main(void){
    Golomb g(3);
    string s="";
    int z=0;
    
    for(z=-15; z< 10; z+=5){
        s = g.signed_encode(z);    
        cout << "golomb code of " << z << " -> "<< s << endl;
        cout << "golomb decode of " << z << " -> "<< g.signed_decode(s) << endl;
    }

}