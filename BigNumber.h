//
// Created by yoanndqr on 07/01/19.
//

#ifndef ADGN_BIGNUMBER_H
#define ADGN_BIGNUMBER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>

using namespace std;

class BigNumber{
public:
    BigNumber(vector<unsigned int> coefs, long unsigned int base, int reverse);
    BigNumber(vector<unsigned int> coefs, long unsigned int base);
    explicit BigNumber(long unsigned int base);

    unsigned int size() {return (unsigned int)m_coef.size();}
    BigNumber& operator = (BigNumber nb);
    void operator >> (int index);
    friend bool operator == (BigNumber& value1, BigNumber& value2);
    friend bool operator > (BigNumber& value1, BigNumber& value2);
    friend bool operator >= (BigNumber& value1, BigNumber& value2);
    void operator << (int index);
    friend ostream& operator << (ostream& os, BigNumber nb2 );
    friend BigNumber operator + (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator + (BigNumber nb1, unsigned int nb2);
    friend BigNumber operator + (unsigned int nb1, BigNumber nb2);
    friend BigNumber operator - (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator - (BigNumber nb1, unsigned int nb2);
    friend BigNumber operator * (BigNumber nb1, BigNumber nb2);
    friend BigNumber operator / (BigNumber nb1, BigNumber nb2);
    friend BigNumber partial_multiplication(BigNumber& nb1, BigNumber& nb2, unsigned int r);
    BigNumber m_square_and_multiply(BigNumber &e, BigNumber &N, int r, BigNumber &v, BigNumber &real_r2);
    BigNumber m_slice(unsigned int deb, unsigned int end);
    void m_mask(int r);

    long unsigned int m_base;
    vector<unsigned int> m_coef;

private:
    void m_format();

};

ostream& operator << (ostream& os, BigNumber nb);
BigNumber operator + (BigNumber nb1, BigNumber nb2);
BigNumber operator + (BigNumber nb1, unsigned int nb2);
BigNumber operator + (unsigned int nb1, BigNumber nb2);
BigNumber operator * (BigNumber nb1, BigNumber nb2);
BigNumber operator - (BigNumber nb1, BigNumber nb2);
BigNumber operator - (BigNumber nb1, unsigned int nb2);
BigNumber operator / (BigNumber nb1, BigNumber nb2);
BigNumber partial_multiplication(BigNumber& nb1, BigNumber& nb2, unsigned int r);
BigNumber montgomery(BigNumber &a, BigNumber &b, BigNumber &n, int r, BigNumber &v);
void representation_binaire(unsigned int decimal, char *representation, double size);
void add(unsigned int *a, unsigned int b, int *retenue, long unsigned int base);

#endif //RSA_BIGNUMBER_H
