#include <iostream>

using namespace std;

int n;
int v[1001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    for(int i = 1; i <= n; i++) {
        int val = -1;
        for(int j = i + 1; j <= n; j++) {
            if(v[i] < v[j]) {
                val = v[j]; break;
            }
        }
        cout << val << " ";
    }
    return 0;
}
