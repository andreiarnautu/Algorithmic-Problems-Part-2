/**
  *  Worg
  */
#include <iostream>

using namespace std;

int main() {
    int P, K; cin >> P >> K;

    /** Nu ne intereseaza ultima cifra a numarului, ci ceea ce este inaintea ei.
        Observam sirul de numere care se adauga, pe rand, inaintea cifrei: 0, 1, 3, 4, 6, 7, ..
        Pe scurt, se sar multiplii de 3 + 2.

        Observam ca putem sa grupam cate 2 aceste numere: (0, 1); (3, 4); (6, 7); ..
        Pe scurt, grupa X va avea elementele: (3 * (X - 1), 3 * (X - 1) + 1)

        -> In ce grupa se va afla al K-lea element? In grupa (K + 1) / 2.
        -> Daca K % 2 == 1, atunci va fi primul numar din grupa gasita, altfel va fi cel de al doilea */

    int Group = (K + 1) / 2;
    int Element;

    if(K % 2 == 1) {
        Element = 3 * (Group - 1);
    } else {
        Element = 3 * (Group - 1) + 1;
    }

    cout << Element << P;

    return 0;
}
