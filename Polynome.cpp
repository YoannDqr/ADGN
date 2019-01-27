//
// Created by yoanndqr on 25/01/19.
//

#include "Polynome.h"

Polynome::Polynome(vector<unsigned int> coefs, int reverse){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->m_coef.emplace_back(coefs[coefs.size() - 1 - i]);
    }
}

Polynome::Polynome(vector<unsigned int> coefs){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->m_coef.emplace_back(coefs[i]);
    }
}

Polynome::Polynome(){
    this->m_coef.emplace_back(0);
}

Polynome Polynome::m_slice(unsigned int deb, unsigned int length) {
    Polynome tmp;
    if(deb < m_degre()){
        for(unsigned int i = deb; i < min(m_degre(),deb + length); i++){
            if(i == deb){
                tmp.m_coef[0] = m_coef[i];
            }
            else {
                tmp.m_coef.emplace_back(m_coef[i]);
            }
        }
    }
    return tmp;
}

