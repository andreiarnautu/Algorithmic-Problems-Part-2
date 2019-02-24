/**
  *  Worg
  */
#include <iostream>

using namespace std;

int main() {
    int N; cin >> N;

    /** Fie Q dupa un anumit numar de operatii de forma (M3 + a) ;
        La pasul urmator trebuie sa adaugam la inceputul lui Q un numar de forma (M3 + b) ;
        Observam ca dupa aceasta adaugare Q va deveni de forma (M3 + (a + b) % 3) ;
        Studiem cum evolueaza formele lui Q:
            -> dupa adaugarea lui 1, Q = M3 + 1
            -> dupa adaugarea lui 2, Q = M3 + 1 + 2 = M3
            -> dupa adaugarea lui 3, Q = M3
            -> dupa adaugarea lui 4, Q = M3 + 1
                        .
                        .
                        .

        Observam ca formele lui Q se repeta din 3 in 3, acesta fiind M3 dupa adaugarea a (M3) sau (M3 + 2) numere la inceput.

        Astfel, pentru a afla numarul de numere divizibile cu 3 din cele N, scadem din N numarul de multiplii de 3 din intervalul
        [1, N] ;
        */

    int Count = (N - 1) / 3 + 1;

    cout << (N - Count);

    return 0;
}
