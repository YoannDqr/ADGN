#include "BigNumber.h"

using namespace std;
BigNumber multiplication_modulaireGN(BigNumber& a, BigNumber& b, BigNumber& n, int r, BigNumber& v, BigNumber& real_r2);

BigNumber multiplication_modulaireGN(BigNumber& a, BigNumber& b, BigNumber& n, int r, BigNumber& v, BigNumber& real_r2){
    BigNumber unite({1}, a.val_base);
    BigNumber a1 = montgomery(a, real_r2, n, r, v);
    BigNumber b1 = montgomery(b, real_r2, n, r, v);
    BigNumber c = b1;
    c = montgomery(c, c, n, r, v);
    c = montgomery(c, b1, n, r, v);

    return montgomery(c, unite, n, r, v);
}

//int main(){
//
//    long unsigned int base = 10;
//    BigNumber m ({1, 1}, base, 1);
//    BigNumber e ({1,3}, base, 1);
//    BigNumber n ({2,1}, base, 1);
//    BigNumber v ({1,9}, base, 1);
//    BigNumber d ({1}, base, 1);
//    BigNumber real_r2 ({4}, base, 1);
//    int r = n.size();
//
//    BigNumber resultat = square_and_multiply(m, e, n, r, v, real_r2);
//    resultat = square_and_multiply(resultat, d, n, r, v, real_r2);
//    cout << resultat << endl;
//
//
//
//    return 0;
//}

int main() {

    long unsigned int base = 4294967296;

    vector <unsigned int> p1 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75};
    vector <unsigned int> q1 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145};
    vector <unsigned int> e1 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 285};
    vector <unsigned int> n1 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10875};
    vector <unsigned int> v1 = {1295810598, 567934108, 1462085356, 489085113, 3474155137, 363905627, 3554194397, 2672956310, 1462788076, 386586051, 1045080972, 584698610, 415168777, 3068734737, 3564255822, 1704807014, 3640413780, 3181632784, 4176880379, 343992323, 865312491, 2334487511, 1789470971, 3377127848, 432853715, 2287094768, 3608167468, 693513799, 3021682278, 3335659198, 1487342237, 3697028860, 2115296077};
    vector <unsigned int> d1 = {2366988799, 3777567450, 4256133434, 3715635382, 2102803053, 538910050, 2658892395, 2033075339, 2739880485, 223619520, 286417771, 1478718362, 3618622911, 2363957160, 698720772, 3590039000, 325540360, 306051247, 2601868696, 160532541, 846116208, 2547732272, 2242835935, 1222905716, 1111601229, 2197361339, 2284845799, 4005084793, 2365400798, 528660221, 430348475, 4280536789};
    vector <unsigned int> real_r21 = {4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4289104296, 0, 219, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 3886882921, 0, 10875};
    vector <unsigned int> inv_r = {1295810598, 567934108, 1462085356, 489085113, 3474155137, 363905627, 3554194397, 2672956310, 1462788076, 386586051, 1045080972, 584698610, 415168777, 3068734737, 3564255822, 1704807081, 955936537, 3573085035, 3713111524, 568534961, 675263962, 789347009, 2028190576, 3016996571, 123683255, 1436680122, 1597747354, 478189140, 4164500159, 4147436048, 3939575293, 797453360};

    BigNumber encrypt (e1, base, 1);
    BigNumber p (p1, base, 1);
    BigNumber q (q1, base, 1);
    BigNumber decrypt (d1, base, 1);
    BigNumber v (v1, base, 1);
    BigNumber m({1,2,3,4, 1462085356, 489085113, 3474155137, 363905627, 567934108, 1462085356, 489085113, 3474155137, 363905627,1295810598, 567934108, 1462085356, 489085113, 3474155137, 363905627,1295810598, 567934108, 1462085356, 489085113, 3474155137, 363905627, 3554194397, 2672956310, 1462788076,1212, 86537}, base, 1);
    BigNumber real_r2 (real_r21, base, 1);
    BigNumber n = p*q;
    int r = (int)n.size();

    BigNumber resultat = square_and_multiply(m, encrypt, n, r, v, real_r2);
    cout << "Cipher : " << resultat << endl;
    resultat = square_and_multiply(resultat, decrypt, n, r, v, real_r2);
    cout << "Plaintext : " << resultat << endl;



    return 0;
}

