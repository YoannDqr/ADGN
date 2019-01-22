//
// Created by yoanndqr on 07/01/19.
//

#ifndef RSA_BIGNUMBER_H
#define RSA_BIGNUMBER_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class BigNumber{
public:
    BigNumber(vector<unsigned int> coefs, long unsigned int base, int reverse);
    BigNumber(vector<unsigned int> coefs, long unsigned int base);
    void mask(int r){
        vector<unsigned int> tmp;
        for (unsigned int i = 0; i < this->size(); i ++){
            if(i < r){
                tmp.emplace_back(this->coef[i]);
            }
        }
        this->coef = tmp;
    }
    BigNumber& operator = (BigNumber nb);
    int size(){return this->coef.size();}
    void operator >> (int index);
    bool operator >= (BigNumber value);
    friend ostream& operator << (ostream& os, BigNumber nb2 );
    void operator << (const int index);
    friend BigNumber operator + (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator - (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator * (BigNumber nb1, BigNumber nb2);
    friend BigNumber quick_expGN(BigNumber& m, BigNumber& e, BigNumber& N, int r, BigNumber& v, BigNumber& real_r2 );
    friend BigNumber MontgomeryGN(BigNumber& a, BigNumber& b, BigNumber& n, int r, BigNumber& v);
    long unsigned int val_base;

private:
    vector<unsigned int> coef;

};

ostream& operator << (ostream& os, BigNumber nb );
BigNumber operator + (BigNumber nb1, BigNumber nb2);
BigNumber operator * (BigNumber nb1, BigNumber nb2);

BigNumber MontgomeryGN(BigNumber& a, BigNumber& b, BigNumber& n, int r, BigNumber& v);
BigNumber quick_expGN(BigNumber& m, BigNumber& e, BigNumber& N, int r, BigNumber& v );
void representation_binaire(unsigned int decimal, char *representation, double size, int base);

#endif //RSA_BIGNUMBER_H
