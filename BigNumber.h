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

    explicit BigNumber(long unsigned int base);
    void mask(int r);
    BigNumber& operator = (BigNumber nb);
    unsigned long size(){return this->coef.size();}
    void operator >> (int index);
    friend bool operator == (BigNumber& value1, BigNumber& value2);
    friend bool operator > (BigNumber& value1, BigNumber& value2);
    friend bool operator >= (BigNumber& value1, BigNumber& value2);
    void operator << (int index);
    friend ostream& operator << (ostream& os, BigNumber nb2 );

    friend BigNumber operator + (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator - (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator * (BigNumber nb1, BigNumber nb2);
    friend BigNumber square_and_multiply(BigNumber &m, BigNumber &e, BigNumber &N, int r, BigNumber &v,
                                         BigNumber &real_r2);
    friend BigNumber montgomery(BigNumber &a, BigNumber &b, BigNumber &n, int r, BigNumber &v);

    void format();

    long unsigned int val_base;

private:
    vector<unsigned int> coef;

};

ostream& operator << (ostream& os, BigNumber nb );
BigNumber operator + (BigNumber nb1, BigNumber nb2);
BigNumber operator * (BigNumber nb1, BigNumber nb2);

BigNumber montgomery(BigNumber &a, BigNumber &b, BigNumber &n, int r, BigNumber &v);
BigNumber square_and_multiply(BigNumber &m, BigNumber &e, BigNumber &N, int r, BigNumber &v);
void representation_binaire(unsigned int decimal, char *representation, double size, int base);
void add(unsigned int *a, unsigned int b, int *retenue, long unsigned int base);

#endif //RSA_BIGNUMBER_H
