#include <iostream>

using namespace std;

int n;
int v[1001];

int main() {
    int minim = 1000000001, pos = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        if(v[i] < minim) {
            minim = v[i]; pos = i;
        }
    }

    bool ok = true;
    if(pos == 1 || pos == n) {
        ok = false;  //  Trebuie sa aiba si la stanga si la dreapta elemente
    }
    for(int i = 1; i < pos; i++) {
        if(v[i] <= v[i + 1]) {
            ok = false;
        }
    }
    for(int i = pos; i < n; i++) {
        if(v[i] >= v[i + 1]) {
            ok = false;
        }
    }

    if(ok == true) {
        cout << "DA";
    } else {
        cout << "NU";
    }

    return 0;
}
