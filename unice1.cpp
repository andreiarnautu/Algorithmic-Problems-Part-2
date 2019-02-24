#include <fstream>

using namespace std;
ifstream cin("unice1.in");
ofstream cout("unice1.out");

int n;
int v[1001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    int sol = 0;
    for(int i = 1; i <= n; i++) {
        bool ok = true;
        for(int j = 1; j <= n; j++) {
            if(i != j && v[i] == v[j]) {
                ok = false;
            }
        }
        if(ok) {
            sol ++;
        }
    }
    cout << sol;
    return 0;
}
