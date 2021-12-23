#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <vector>

#include "Golomb.h"
#include "../BitStream/bitstream.h"


using namespace std;

string Golomb::unary(int q){
    std::string unr(q, '1');
    return unr+"0";
}

string Golomb::binary(int x, int n){
    int i, q=x;
    string b;
    for(i=0; i<n; i++){
        if(q == 0) b = "0" + b;
        else{
            b = to_string(q%2) + b;
            q = q/2;
        }
    }
    return b;
}


int Golomb::decimal(string a){
    int i, j=0, res=0;
    for(i=a.length()-1; i>=0; i--){
        res += (a[j++]-48)*pow(2,i);
    }
    return res;
}

Golomb::Golomb(int m){
    this->m = m;
    this->b = ceil(log2(m));
}

string Golomb::encode(signed int n){
    int q = n/this->m, r = n-q*this->m;
    return unary(q) + (r < pow(2,this->b)-this->m? binary(r,this->b-1): binary(r+pow(2,this->b)-this->m,this->b));  
}


int Golomb::decode(string str){
    int a=0, r, rl;
    while(str[a]=='1') a++;
    r = decimal(str.substr(a+1, this->b-1));
    rl = decimal(str.substr(a+1, this->b));
    return this->m*a + (r < pow(2,this->b)-this->m? r : rl - (pow(2,this->b)-this->m));
}

 string Golomb::signed_encode(int n){
    return encode(n>=0?2*n:-2*n-1);
}

int Golomb::signed_decode(string code){
    uint res=decode(code);
    return res%2 ? ((int)res+1)/-2 : res/2;
}

void Golomb::set_m(int m){
    this->m = m;
    this->b = ceil(log2(m));
}
int Golomb::get_m(void){return this->m;}
        

void Golomb::write(string fname, vector<int> v){
    bitstream bs((char*) fname.data(), std::ios::binary|std::ios::out);
    int i, j, sz = int(v.size());
    string golb;
    v.insert(v.begin(), this->m);
    v.insert(v.begin(), sz);
    for(i=0; i<sz+2; i++){
        golb = (i<2? binary(v[i], 16) : signed_encode(v[i]));
        for(j=0; j<int(golb.size()); j++)
            bs.writeBit(  (golb[j]=='0'? 0 : 1)   );
    }
    bs.padding();
}
 

vector<int> Golomb::read(string fname){
    vector<int> rd;
    bitstream bs((char*) fname.data(), std::ios::binary|std::ios::in);
    int i;

    //header em bin:(n_elems, m)
    int elems = decimal(bs.toString(bs.readNBits(16),16));
    this->m = decimal(bs.toString(bs.readNBits(16),16));
    //rd.push_back(elems);
    //rd.push_back(m);

    //ler golomb
    for(int j=0; j<elems; j++){
        i = 0;
        string q(1, bs.readBit()==0? '0':'1' );
        while(q[i++]!='0') q += (bs.readBit()==0? "0":"1");
        string r = bs.toString(bs.readNBits(this->b-1), this->b-1);
        string rl = (decimal(r)<pow(2,this->b)-this->m? "" : (bs.readBit()==0? "0":"1"));
        rd.push_back( signed_decode(q+r+rl) );
    }
    return rd;
}
