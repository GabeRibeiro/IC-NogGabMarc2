#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>

#include "Golomb.h"

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
    int a=0, r, rl, val;
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