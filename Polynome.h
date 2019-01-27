//
// Created by yoanndqr on 25/01/19.
//

#ifndef RSA_POLYNOME_H
#define RSA_POLYNOME_H


#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <string.h>

using namespace std;

class Polynome{
public:
    Polynome(vector<unsigned int> coefs, int reverse);
    explicit Polynome(vector<unsigned int> coefs);
    explicit Polynome();
    unsigned int m_degre() {return (unsigned int)m_coef.size();}
    Polynome m_slice(unsigned int deb, unsigned int length);
    vector<unsigned int> m_coef;
};



#endif //RSA_POLYNOME_H
