/**
  *  Worg
  */
#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("pozitie.in");
ofstream cout("pozitie.out");

int n;
int v[10001];

int main() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    int x = v[1];
    sort(v + 1, v + n + 1);
    for(int i = 1; i <= n; i++) {
        if(x == v[i]) {
            cout << i; return 0;
        }
    }
    return 0;
}
