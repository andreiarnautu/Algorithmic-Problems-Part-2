#include <iostream>

using namespace std;

int main() {

    long long int n, a, b, putere, solutie;      /* grija aici, daca puneti int o sa greseasca pe unele teste, pentru ca ajunge puterea sa iasa din int*/
    cin >> n;
    for(int i = 1; i <= n; ++i) {

        cin >> a >> b;
        if(a > b)
            swap(a, b);
        solutie = 0, putere = 1;
        do {

            if(a <= putere && putere <= b)
                solutie = putere;
            putere *= 2;
        }while(putere < b);

        cout << solutie << '\n';
    }
    return 0;
}
