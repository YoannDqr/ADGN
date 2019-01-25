//
// Created by yoanndqr on 07/01/19.
//

#include "BigNumber.h"

BigNumber::BigNumber(vector<unsigned int> coefs, long unsigned int base, int reverse){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->m_coef.emplace_back(coefs[coefs.size() - 1 - i]);
    }
    this->m_base = base;
}

BigNumber::BigNumber(vector<unsigned int> coefs, long unsigned int base){
    for (unsigned long i = 0; i < coefs.size(); i++) {
        this->m_coef.emplace_back(coefs[i]);
    }
    this->m_base = base;
}

BigNumber::BigNumber(long unsigned int base){
    this->m_base = base;
    this->m_coef.emplace_back(0);
}

bool operator == (BigNumber& value1, BigNumber& value2){
    value1.m_format();
    value2.m_format();
    return value1.m_coef == value2.m_coef;
}

bool operator > (BigNumber& value1, BigNumber& value2){
    value1.m_format();
    value2.m_format();
    if(value1.size() > value2.size()){
        return true;
    }

    else if(value1.size() == value2.size()){
        for(int i = (int)value1.size() - 1; i >= 0; i--){
            if(value1.m_coef[i] > value2.m_coef[i]){
                return true;
            }
            else if(value1.m_coef[i] != value2.m_coef[i]){
                return false;
            }
        }
    }
    return false;

}

bool operator >= (BigNumber& value1, BigNumber& value2){
    return value1 > value2 || value1 == value2;
}

bool operator <= (BigNumber& value1, BigNumber& value2){
    return !(value1 > value2);
}

bool operator != (BigNumber& value1, BigNumber& value2){
    return !(value1 == value2);
}

bool operator < (BigNumber& value1, BigNumber& value2){
    return !((value1 > value2) || (value1 == value2));
}

void BigNumber::operator << (const int index){

    for(int i = 0; i < index; i++){
        this->m_coef.erase(this->m_coef.begin());
    }

}

void BigNumber::operator >> (const int index){
    for (int i = 0; i < index; i++) {
        this->m_coef.insert(this->m_coef.begin(), 0);
    }
}

BigNumber& BigNumber::operator = (BigNumber nb){
    this->m_base = nb.m_base;
    this->m_coef.clear();
    this->m_coef = nb.m_coef;
    return *this;
}

BigNumber BigNumber::m_square_and_multiply(BigNumber &e, BigNumber &N, const int r, BigNumber &v, BigNumber &real_r2){

    unsigned int size = 32;
    char representation[(unsigned long)size];
    BigNumber result ({1}, m_base);
    BigNumber unite ({1}, m_base);
    BigNumber m1 = montgomery(*this, real_r2, N, r, v);
    bool empty = true;

    for(unsigned long i = e.size() ; i > 0; i--){
        representation_binaire(e.m_coef[i - 1], representation, size);
        for(unsigned int j = 0; j < size; j++) {

            if(!empty) {
                result = montgomery(result, result, N, r, v);
            }
            if (representation[j] == '1') {
                if(empty){
                    result = m1;
                    empty = false;
                }
                else {
                    result = montgomery(result, m1, N, r, v);
                }
            }
        }

    }
    result = montgomery(result, unite, N, r, v);
    return result;
}

ostream& operator << (ostream& os, BigNumber nb ){
    for (unsigned long i = 0; i < nb.m_coef.size(); i++) {
        os << nb.m_coef[nb.m_coef.size() - 1 - i] << " ";
    }
    os << endl;
    return os;
}

BigNumber operator + (BigNumber nb1, BigNumber nb2){
//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();
    vector<unsigned int> coef;
    int retenue = 0;
    for(unsigned long i = 0; i < max(nb1.m_coef.size(), nb2.m_coef.size()); i++){
        coef.emplace_back(retenue);
        retenue = 0;

        if( i < nb1.m_coef.size()){
            add(&coef[i], nb1.m_coef[i], &retenue, nb1.m_base);
        }

        if( i < nb2.m_coef.size()){
            add(&coef[i], nb2.m_coef[i], &retenue, nb2.m_base);
        }
    }
    if(retenue){
        coef.emplace_back(1);
    }
    BigNumber result(coef,nb1.m_base);
//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << " Addition : " << t_tmp/cmp << endl;
    return result;
}

BigNumber operator + (BigNumber nb1, unsigned int nb2) {
    BigNumber tmp({nb2}, nb1.m_base);
    return nb1 + tmp;
}

BigNumber operator + (unsigned int nb1, BigNumber nb2) {
    BigNumber tmp({nb1}, nb2.m_base);
    return nb2 + tmp;
}

BigNumber operator - (BigNumber nb1, BigNumber nb2) {
    /*
     * TODO : A refaire ^^
     */
//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();
    BigNumber tmp ({}, nb2.m_base);
    int retenue = 0;
    if(nb1 > nb2) {
        for (unsigned int i = 0; i < max(nb1.m_coef.size(), nb2.m_coef.size()); i++) {
            if (i < nb1.m_coef.size() && i < nb2.m_coef.size()) {
                if (nb1.m_coef[i] >= nb2.m_coef[i]) {
                    if (retenue && nb2.m_base - nb2.m_coef[i] == 1) {
                        tmp.m_coef.emplace_back(nb1.m_coef[i]);
                        retenue = 1;
                    } else {
                        if (nb1.m_coef[i] != nb2.m_coef[i]) {
                            tmp.m_coef.emplace_back(nb1.m_coef[i] - nb2.m_coef[i] - retenue);
                            retenue = 0;
                        } else if (nb1.m_coef[i] == 0) {
                            tmp.m_coef.emplace_back(0);
                        } else {
                            tmp.m_coef.emplace_back(nb1.m_base * retenue - retenue);
                        }

                    }

                } else {
                    tmp.m_coef.emplace_back(nb1.m_base - nb2.m_coef[i] - retenue);
                    tmp.m_coef[i] += nb1.m_coef[i];
                    retenue = 1;
                }
            } else if (i < nb1.m_coef.size()) {
                if (retenue == 0) {
                    tmp.m_coef.emplace_back(nb1.m_coef[i]);
                } else {
                    if (nb1.m_coef[i] == 0) {
                        tmp.m_coef.emplace_back(nb1.m_base - 1);
                    } else {
                        tmp.m_coef.emplace_back(nb1.m_coef[i] - 1);
                        retenue = 0;
                    }
                }

            }
        }
        tmp.m_format();
    }


//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << " Soustraction : " << t_tmp << endl;
    return tmp;
}

BigNumber operator - (BigNumber nb1, unsigned int nb2) {
    BigNumber tmp ({nb2}, nb1.m_base);
    return nb1 - tmp;
}

BigNumber operator * (BigNumber nb1, BigNumber nb2) {
    BigNumber resultat =  partial_multiplication(nb1, nb2, 2 * (unsigned int)nb1.m_coef.size() + 1);
    return resultat;
}

void BigNumber::m_format(){
    int i = 0;
    unsigned int m_size = size();
    while((i < m_size) && (m_coef[m_size-1-i] == 0) && m_coef.size() > 1){
        m_coef.erase(m_coef.begin() + m_size-1-i);
        i++;
    }
}

BigNumber montgomery(BigNumber &a, BigNumber &b, BigNumber &n, int r, BigNumber &v){

//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();

    BigNumber s = a*b;
    //BigNumber t = s*v;
    BigNumber t = partial_multiplication(s, v, r);
    t.m_mask(r);
    BigNumber m = s + t*n;
    BigNumber u = m;

    u << r;
    if(u >= n){
        u = u - n;
    }
//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << " Montgomery : " << t_tmp/(float)cmp << endl;
    return u;

}

void BigNumber::m_mask(int r) {
    vector<unsigned int> tmp;
    for (unsigned int i = 0; i < this->size(); i ++){
        if(i < r){
            tmp.emplace_back(this->m_coef[i]);
        }
    }
    m_coef = tmp;
}

BigNumber partial_multiplication(BigNumber& nb1, BigNumber& nb2, const unsigned int r){
//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();
    const unsigned int SIZE_INT16 = 65536;
    BigNumber resultat(nb1.m_base);
    for(unsigned long i = 0; i < nb1.size() ; i++) {
        unsigned int retenue = 0;
        vector<unsigned int> resultat_intermedaire;

        /*
         * On split la valeur du m_coef de 32 bits en deux valeurs de 16 bits
         * On a m_coef = [high1 low1]
         */
        const unsigned int high1 = (nb1.m_coef[i] >> 16);
        const unsigned int low1 = (nb1.m_coef[i] & 0x0000FFFF);

        for (unsigned long j = 0; j < nb2.m_coef.size(); j++) {
            /*
             * Calcul des résultats intermédiaires des sous-blocks de 16bits des opérandes
             */
            if(i + j < r) {

                const unsigned int high2 = (nb2.m_coef[j] >> 16);
                const unsigned int low2 = (nb2.m_coef[j] & 0x0000FFFF);

                /*
                 * On multiplie de nombre de 16 bits; le résultat sera inferieur a 32bits donc pas d'overflow
                 */
                const unsigned int res1 = low1 * low2;
                const unsigned int res2 = high2 * low1;
                const unsigned int res3 = low2 * high1;
                const unsigned int res4 = high1 * high2;


                /*
                 * Calcul du résultat de la multiplication sur 32 bits
                 */


                unsigned int resultat32b = 0;

                /*
                 * Le resultat de la multiplication est donné par [left1, right1]
                 * La retenue est donné par [left2, right2]
                 */
                unsigned int right2 = 0;
                unsigned int left2 = 0;
                unsigned int left1 = 0;
                /*
                 * On initialise a la valeur de la retenue précédente
                 */
                unsigned int right1 = retenue;
                retenue = 0;

                /*
                 * Valeurs sur 16bits ! Si ca dépasse on fait passer l'exédent sur les 16bits suivants
                 * right1 -> left1
                 * left1 -> right2
                 * right2 -> left2
                 * left2 -> retenue
                 */
                left1 = right1 / SIZE_INT16;
                right1 = right1 % SIZE_INT16;

                /*
                 * On additionne avec prudence en vérifiant les overflows possible
                 * pour former le résultat et la retenue sur 32 bits
                 */
                if (SIZE_INT16 - right1 > (res1 & 0x0000FFFF)) {
                    right1 += (res1 & 0x0000FFFF);
                } else {
                    right1 -= SIZE_INT16;
                    right1 += (res1 & 0x0000FFFF);
                    left1 += 1;
                }

                if (SIZE_INT16 - left1 > (res1 >> 16)) {
                    left1 += (res1 >> 16);
                } else {
                    left1 -= SIZE_INT16;
                    left1 += (res1 >> 16);
                    right2 += 1;
                }

                if (SIZE_INT16 - left1 > (res2 & 0x0000FFFF)) {
                    left1 += (res2 & 0x0000FFFF);
                } else {
                    left1 -= SIZE_INT16;
                    left1 += (res2 & 0x0000FFFF);
                    right2 += 1;
                }

                if (SIZE_INT16 - left1 > (res3 & 0x0000FFFF)) {
                    left1 += (res3 & 0x0000FFFF);
                } else {
                    left1 -= SIZE_INT16;
                    left1 += (res3 & 0x0000FFFF);
                    right2 += 1;
                }

                /*
                 * Calcul de la retenue
                 */

                if (SIZE_INT16 - right2 > (res4 & 0x0000FFFF)) {
                    right2 += (res4 & 0x0000FFFF);
                } else {
                    right2 -= SIZE_INT16;
                    right2 += (res4 & 0x0000FFFF);
                    left2 += 1;
                }

                if (SIZE_INT16 - right2 > (res2 >> 16)) {
                    right2 += (res2 >> 16);
                } else {
                    right2 -= SIZE_INT16;
                    right2 += (res2 >> 16);
                    left2 += 1;
                }

                if (SIZE_INT16 - right2 > (res3 >> 16)) {
                    right2 += (res3 >> 16);
                } else {
                    right2 -= SIZE_INT16;
                    right2 += (res3 >> 16);
                    left2 += 1;
                }

                if (SIZE_INT16 - left2 > (res4 >> 16)) {
                    left2 += (res4 >> 16);
                } else {
                    left2 -= SIZE_INT16;
                    left2 += (res4 >> 16);
                    retenue += 1;
                }

                retenue += (left2 << 16) + right2;
                resultat32b += (left1 << 16) + right1;
                if (nb1.m_base < 4294967296) {
                    resultat32b = resultat32b % (unsigned int) nb1.m_base;
                    retenue = resultat32b / (unsigned int) nb1.m_base;
                }
                resultat_intermedaire.emplace_back(resultat32b);
            }
        }

        if(retenue != 0){
            resultat_intermedaire.emplace_back(retenue);
        }
        BigNumber tmp(resultat_intermedaire, nb1.m_base);
        tmp >> i;
        resultat = resultat + tmp;
    }
//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << "Multiplication : " << t_tmp / (float)cmp << endl;

    return resultat;
}

BigNumber operator / (BigNumber nb1, BigNumber nb2) {
//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();

    BigNumber quotient(nb1.m_base);
    BigNumber val = nb1.m_slice(nb1.size() - nb2.size(), nb2.size());

    if(nb2 > val){
        val >> 1;
        val = val + nb1.m_slice(nb1.size() - nb2.size() - 1, 1);
    }

    unsigned int quotient_size = nb1.size() - val.size();

    for(unsigned int i = 0; i < quotient_size; i++){
        quotient.m_coef.emplace_back(0);
    }

    for(unsigned int i = 0; i < quotient_size + 1; i++){
        while(val >= nb2){
            quotient.m_coef[quotient_size - i] += 1;
            val = val - nb2;
        }
        val >> 1;
        val = val + nb1.m_slice(quotient_size - i - 1, 1);
    }
//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << " Division : " << (t2 - t1)/(float)cmp << endl;
    return quotient;
}

BigNumber BigNumber::m_slice(unsigned int deb, unsigned int length) {
    BigNumber tmp(m_base);
    if(deb < size()){
        for(unsigned int i = deb; i < min(size(),deb + length); i++){
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

void representation_binaire(const unsigned int decimal, char *representation, const double size){
    unsigned int val = decimal;
    auto bit_val = (unsigned int)pow(2, size - 1);
    unsigned long bit_pointer = 0;
//    clock_t t1, t2;
//    static clock_t t_tmp;
//    static unsigned int cmp = 0;
//    t1 = clock();

    while(bit_pointer < size){
        representation[bit_pointer] = val >= bit_val ? '1' : '0';
        val -= val >= bit_val ? bit_val : 0;
        bit_val /= 2;
        bit_pointer += 1;
    }
//    t2 = clock();
//    t_tmp += (t2 - t1);
//    cmp += 1;
//    cout << " Binaire : " << (t2 - t1)/(float)cmp << endl;

}

void add(unsigned int *a, const unsigned int b, int *retenue, const long unsigned int base) {
    /**
     * Addition avec overflow p/r a la base
     */
    if(base - *a > b) {
        *a += b;
    }
    else{
        *retenue = 1;
        *a -= base;
        *a += b;
    }
}
