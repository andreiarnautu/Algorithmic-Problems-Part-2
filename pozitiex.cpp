#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("pozitiex.in");
ofstream cout("pozitiex.out");

int n, x;
int v[10001];

int main() {
    cin >> x >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    sort(v + 1, v + n + 1);

    int pos = 0;
    for(int i = 1; i <= n; i++) {
        if(x == v[i]) {
            pos = i; break;
        }
    }

    if(pos == 0) {
        cout << "NU EXISTA";
    } else {
        cout << pos;
    }
    return 0;
}
