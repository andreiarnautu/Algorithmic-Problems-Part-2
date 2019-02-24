/**
  *  Worg
  */
#include <iostream>

using namespace std;

int u_cif[10];

int main() {
    for(int i = 1; i <= 9; i++) {
        u_cif[i] = (i * i * i * i) % 10;
    }

    int n; cin >> n;

    int sol = 0;
    sol = (n / 10) * 3;

    for(int i = 1; i <= n % 10; i++) {
        sol += u_cif[i];
    }
    cout << sol % 10;

    return 0;
}
