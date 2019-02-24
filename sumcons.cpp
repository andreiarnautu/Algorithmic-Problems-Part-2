/**
  *  Worg
  */
#include <iostream>

using namespace std;

int main() {

    /*
        Se citeste n.
        Daca avem k termeni consecutivi, suma lor va fi:
        (x + 1) + (x + 2) + ... + (x + k) =
        = x * k + k * (k + 1) / 2 = n
        De unde obtinem x = (2 * n - k * (k + 1)) / (2 * k).
        Observam ca mereu k si x sunt naturale. De asemenea, k * (k + 1) <= 2 * n,
        deci iteratiile vor merge pana la o valoarea apropiata de sqrt(n), care vor intra sigur in timp */

    int n;
    cin >> n;

    for(int k = 2; k * (k + 1) <= (2 * n); ++k) {

        int x = (2 * n - k * (k + 1)) / (2 * k);

        if((2 * n - k * (k + 1)) % (2 * k) == 0) {    /* verificam daca x este natural */

            for(int i = 1; i <= k; ++i)
                cout << x + i << " ";
            cout << '\n';
        }
    }
    return 0;
}
