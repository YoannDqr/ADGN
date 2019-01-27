Arithmétique sur les grands nombres
==================================

Polynôme :
----------
Cet objet modélise un polynôme. 

#### Attributs 
* `vector <unsigned int> m_coef ` : tableau des coefficients du polynôme

BigNumber : 
-----------
Cet objet modélise un grand nombre. Il est hérité de la classe Polynôme.
Ainsi, le nombre est stocké sous forme d'un polynôme dont les coefficients
sont les coefficients de ce nombre décomposé dans la base donnée.

#### Attributs 
* `vector <unsigned int> m_coef ` : tableau de coefficient hérité 
des polynômes
* `long unsigned int m_base` : base relative à la décomposition du nombre

#### Méthodes 
* `BigNumber operator +(BigNumer&, BigNumber&)` : méthode d'addition 
scolaire de deux grands nombres avec gestion de dépassement.
Addition des coefficients un à un et propagation de la retenue.

* `BigNumber operator -(BigNumer&, BigNumber&)` : méthode de soustraction
scolaire avec gestion de dépassement.

* `BigNumber operator *(BigNumer&, BigNumber&)` : méthode de multiplication 
de deux grands nombres. Afin d'éviter les overflows, chaque calcul est effectué
sur des entiers de 16bits. 

* `BigNumber m_square_and_multiply(BigNumber&, BigNumber&, int, BigNumber&, BigNumber&)`:
Algorithme d'exponentiation rapide. Les multiplications modulaires sont appliquées 
via la fonction `BigNumber Montgomery(BigNumber&, BigNumber&, BigNumber&, int, BigNumber&)`

#### Fonctions relatives 

* `BigNumber Montgomery(BigNumber&, BigNumber&, BigNumber&, int, BigNumber&)`:
Cette fonction met en place l'algorithme de Montgomery pour des grands nombres.
Afin d'accélérer les calculs, la multiplication __t = sv__ n'est effectué que pour les 
x premiers bits (avec __x = floor(log2(r))__).

#### Temps d'exécution 
Les opérateurs d'addition, multiplication, soustraction, Montgomery,
square and multiply possède les quatre lignes commentées suivantes en début:
 ```c++
     clock_t t1, t2;
     static clock_t t_tmp;
     static unsigned int cmp = 0;
     t1 = clock();
 ```
 Et les lignes suivantes en fin de fonction :
 ```c++
     t2 = clock();
     t_tmp += (t2 - t1);
     cmp += 1;
     cout << " Montgomery : " << t_tmp/(float)cmp << endl;
 ```
 En décommentant ces lignes, vous pourrez observer, en fin d'exécution, 
 le temps moyen mis par le CPU pour exécuter la fonction ciblée.
 
 ##### Multiplication partielle et Montgomery
 Pour visualiser l'effet des multiplications partielles sur le temps 
 moyen d'exécution de l'algorithme de Montgomery, vous pouvez
 décommenter la ligne 247 et commenter la 248 puis relancer le programme.
 
 
 ##### Test sur i7 2coeurs - VM Linux
 
 |Opération                 |Temps moyen     | 
 |:------------------------:|:--------------:|
 |Additon                   | 15 unités      |
 |Soustraction              | 17 unités      |
 |Multiplication            | 1404.03 unités |
 |Montgomery                | 4812.6 unités  |
 |Montgomery + add partielle| 4174.38 unités |
 |RSA                       | 10119360 unités|
 |RSA + add partielle       | 8787428 unités |
