/**
  *  Worg
  */
#include <iostream>

using namespace std;

const int MAX_CIFRE = 1 + 10;

/*-------- Date de intrare --------*/
int N, K;
int x;
/*-------- --------*/

int main() {
    cin >> N >> K;

    /* aceeasi idee va fi aplicata fiecarui numar citit in parte.
       Ideea este sa transformam numarul din baza 10 in baza K.
       Daca in baza K toate cifrele sunt de 1 sau 0, atunci inseamna ca se poate scrie ca suma de puteri distincte ale lui K. */

    int solutie = 0;
    for(int i = 1; i <= N; i++) {
        cin >> x;

        bool este_bun = true;
        while(x != 0) {
            int cifra = x % K;
            x /= K;
            /* observam ca nici macar nu mai este nevoie sa stocam cifrele. Doar trebuie sa verificam daca sunt mai mari ca 1. */

            if(cifra > 1) {
                este_bun = false; break;
            }
        }

        if(este_bun) {
            solutie ++;
        }
    }

    cout << solutie << '\n';
    return 0;
}
