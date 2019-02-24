/**
  *  Worg
  */
#include <iostream>

using namespace std;

int n;
int v[101];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for(int i = 2; i <= n - 1; i++) {
        if(v[i] % 2 == v[i - 1] % 2 && v[i] % 2 == v[i + 1] % 2) {
            cout << "DA"; return 0;
        }
    }
    cout << "NU"; return 0;
}
