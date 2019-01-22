//
// Created by yoanndqr on 07/01/19.
//

#include "BigNumber.h"

BigNumber::BigNumber(vector<unsigned int> coefs, long unsigned int base, int reverse){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->coef.emplace_back(coefs[coefs.size() - 1 - i]);
    }
    this->val_base = base;
}

BigNumber::BigNumber(vector<unsigned int> coefs, long unsigned int base){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->coef.emplace_back(coefs[i]);
    }
    this->val_base = base;
}

bool BigNumber::operator >= (BigNumber value){

    if(this->coef.size() > value.coef.size()){
        return true;
    }

    else if(this->coef.size() == value.coef.size()){
        for(int i = this->size() - 1; i >= 0; i--){
            if(this->coef[i] > value.coef[i]){
                return true;
            }
            else if(this->coef[i] != value.coef[i]){
                return false;
            }
        }
        //return true;
    }
    return false;

}

void BigNumber::operator << (const int index){

    for(int i = 0; i < index; i++){
        this->coef.erase(this->coef.begin());
    }

}

void BigNumber::operator >> (const int index){
    for (int i = 0; i < index; i++) {
        this->coef.insert(this->coef.begin(), 0);
    }
}

BigNumber& BigNumber::operator = (BigNumber nb){
    this->val_base = nb.val_base;
    this->coef.clear();
    for(unsigned long i = 0; i < nb.coef.size(); i++){
        this->coef.emplace_back(nb.coef[i]);
    }
    return *this;
}

ostream& operator << (ostream& os, BigNumber nb ){
    for (unsigned long i = 0; i < nb.coef.size(); i++) {
        os << nb.coef[nb.coef.size() - 1 - i] << " ";
    }
    os << endl;
    return os;
}

BigNumber operator+(const BigNumber nb1, const BigNumber nb2){
    vector<unsigned int> coef;
    int retenue = 0;
    for(unsigned long i = 0; i < max(nb1.coef.size(), nb2.coef.size()); i++){
        coef.emplace_back(retenue);
        retenue = 0;


        if( i < nb1.coef.size()){
            if(nb1.val_base - coef[i] > nb1.coef[i]) {
                coef[i] += nb1.coef[i];
            }
            else{
                retenue = 1;
                coef[i] -= nb1.val_base;
                coef[i] += nb1.coef[i];
            }
        }

        if( i < nb2.coef.size()){
            if(nb2.val_base - coef[i] > nb2.coef[i]) {
                coef[i] += nb2.coef[i];
            }
            else{
                retenue = 1;
                coef[i] -= nb2.val_base;
                coef[i] += nb2.coef[i];
            }
        }
    }
    if(retenue){
        coef.emplace_back(1);
    }
    BigNumber result(coef,nb1.val_base);
    return result;
}

BigNumber operator - (const BigNumber nb1, const BigNumber nb2) {
    BigNumber tmp ({}, nb2.val_base);
    int retenue = 0;
    for(unsigned int i = 0; i < max(nb1.coef.size(), nb2.coef.size()); i++){
        if( i < nb1.coef.size() && i < nb2.coef.size()){
            if(nb1.coef[i] >= nb2.coef[i]){
                if(retenue && nb2.val_base - nb2.coef[i] == 1){
                    tmp.coef.emplace_back(nb1.coef[i]);
                    retenue = 1;
                }
                else {
                    if(nb1.coef[i] != nb2.coef[i]) {
                        tmp.coef.emplace_back(nb1.coef[i] - nb2.coef[i] - retenue);
                        retenue = 0;
                    }
                    else if(nb1.coef[i] == 0){
                        tmp.coef.emplace_back(0);
                    }
                    else{
                        tmp.coef.emplace_back(nb1.val_base*retenue - retenue);
                    }

                }

            }
            else{
                tmp.coef.emplace_back(nb1.val_base - nb2.coef[i] - retenue);
                tmp.coef[i] += nb1.coef[i];
                retenue = 1;
            }
        }
        else if(i < nb1.coef.size()){
            if(retenue == 0) {
                tmp.coef.emplace_back(nb1.coef[i]);
            }
            else{
              if(nb1.coef[i] == 0){
                  tmp.coef.emplace_back(nb1.val_base - 1);
              }
              else{
                  tmp.coef.emplace_back(nb1.coef[i] - 1);
                  retenue = 0;
              }
            }

        }
    }

    int i= 0;
    int size = tmp.size();
    while(i < size && tmp.coef[size-1-i] == 0){
        tmp.coef.erase(tmp.coef.begin() + size-1-i);
        i++;
    }
    return tmp;
}


BigNumber operator*(const BigNumber nb1, const BigNumber nb2) {
    vector<vector<unsigned int>> resultats;
    for(unsigned long i = 0; i < nb1.coef.size(); i++) {
        unsigned int high1 = (nb1.coef[i] >> 16);
        unsigned int low1 = (nb1.coef[i] & 0x0000FFFF);
        unsigned int retenue = 0;
        vector<unsigned int> res_int;
        for (unsigned long j = 0; j < nb2.coef.size(); j++) {
            /*
             * Calcul des résultats intermédiaires des sous-blocks de 16bits des opérandes
             */

            unsigned int high2 = (nb2.coef[j] >> 16);
            unsigned int low2 = (nb2.coef[j] & 0x0000FFFF);

            /*
             * On multiplie de nombre de 16 bits; le résultat sera inferieur a 32bits donc pas d'overflow
             */
            unsigned int res1 = low1 * low2;
            unsigned int res2 = high2 * low1;
            unsigned int res3 = low2 * high1;
            unsigned int res4 = high1 * high2;


            /*
             * Calcul du résultat de la multiplication sur 32 bits
             */
            unsigned int maxBase = 65536;
            unsigned int resultat = 0;
            unsigned int right2 = 0;
            unsigned int left2 = 0;
            unsigned int left1 = 0;
            unsigned int right1 = retenue;
            retenue = 0;
            while(right1 > maxBase){
                left1 += 1;
                right1 -= maxBase;
            }
            if(maxBase - right1 > (res1 & 0x0000FFFF)){
                right1 += (res1 & 0x0000FFFF);
            }
            else{
                right1 -= maxBase;
                right1 += (res1 & 0x0000FFFF);
                left1 += 1;
            }

            if(maxBase - left1 > (res1 >> 16)){
                left1 += (res1 >> 16);
            }
            else{
                left1 -= maxBase;
                left1 += (res1 >> 16);
                right2 += 1;
            }

            if(maxBase - left1 > (res2 & 0x0000FFFF)){
                left1 += (res2 & 0x0000FFFF);
            }
            else{
                left1 -= maxBase;
                left1 += (res2 & 0x0000FFFF);
                right2 += 1;
            }

            if(maxBase - left1 > (res3 & 0x0000FFFF)){
                left1 += (res3 & 0x0000FFFF);
            }
            else{
                left1 -= maxBase;
                left1 += (res3 & 0x0000FFFF);
                right2 += 1;
            }

            /*
             * Calcul de la retenue
             */

            if(maxBase - right2 > (res4 & 0x0000FFFF)){
                right2 += (res4 & 0x0000FFFF);
            }
            else{
                right2 -= maxBase;
                right2 += (res4 & 0x0000FFFF);
                left2 += 1;
            }

            if(maxBase - right2 > (res2 >> 16)){
                right2 += (res2 >> 16);
            }
            else{
                right2 -= maxBase;
                right2 += (res2 >> 16);
                left2 += 1;
            }

            if(maxBase - right2 > (res3 >> 16)){
                right2 += (res3 >> 16);
            }
            else{
                right2 -= maxBase;
                right2 += (res3 >> 16);
                left2 += 1;
            }

            if(maxBase - left2 > (res4 >> 16)) {
                left2 += (res4 >> 16);
            }
            else{
                left2 -= maxBase;
                left2 += (res4 >> 16);
                retenue += 1;
            }

            retenue += (left2 << 16) + right2;
            resultat += (left1 << 16) + right1;
            while(resultat >= nb1.val_base) {
                //Uniquement pour des bases inférieur a 2^32
                resultat -= nb1.val_base;
                retenue += 1;
            }
            res_int.emplace_back(resultat);
        }

        if(retenue != 0){
            res_int.emplace_back(retenue);
        }
        resultats.emplace_back(res_int);
    }
    vector <unsigned int> coef;
    coef.emplace_back(0);
    BigNumber res(coef, nb1.val_base);
    for(unsigned long i = 0; i < resultats.size(); i++){
        BigNumber tmp(resultats[i], nb1.val_base);
        for(unsigned int j = 0; j < i; j++){
            tmp.coef.insert(tmp.coef.begin(), 0);
        }
        res = res + tmp;
    }
    return res;
}

BigNumber MontgomeryGN(BigNumber& a, BigNumber& b, BigNumber& n, int r, BigNumber& v){

    BigNumber s = a*b;
    BigNumber t = s*v;
    t.mask(r);
    BigNumber tmp = t*n;
    BigNumber m = s + tmp;
    BigNumber u = m;

    u << r;
    if(u >= n){
        u = u - n;
    }
    return u;

}



BigNumber quick_expGN(BigNumber& m, BigNumber& e, BigNumber& N, int r, BigNumber& v, BigNumber& real_r2 ){

    unsigned int size = 32;
    char representation[(unsigned long)size];
    BigNumber resultat ({1}, m.val_base);
    BigNumber unite ({1}, m.val_base);
    BigNumber m1 = MontgomeryGN(m,real_r2,N,r,v);
    bool empty = true;

    for(double i = e.size()-1; i >= 0; i--){
        representation_binaire(e.coef[i], representation, size, 2);
        for(unsigned int j = 0; j < size; j++) {

            if(!empty) {
                resultat = MontgomeryGN(resultat, resultat, N, r, v);
            }
            if (representation[j] == '1') {
                if(empty){
                    resultat = m1;
                    empty = false;
                }
                else {
                    resultat = MontgomeryGN(resultat, m1, N, r, v);
                }
            }
        }

    }
    resultat = MontgomeryGN(resultat,unite,N,r,v);
    return resultat;
}

void representation_binaire(const unsigned int decimal, char *representation, double size, int base){
    unsigned int val = decimal;
    auto bit_val = (unsigned int)pow(base, size - 1);
    unsigned long bit_pointer = 0;

    while(bit_pointer < size){
        if(val >= bit_val){
            val -= bit_val;
            representation[bit_pointer] = '1';
        }
        else{
            representation[bit_pointer] = '0';
        }
        bit_val /= base;
        bit_pointer += 1;
    }
}