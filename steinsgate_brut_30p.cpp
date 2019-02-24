/**
  *  Worg
  *  O(N * K) - 30p
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("steinsgate.in", "r", stdin);
FILE *fout = freopen("steinsgate.out", "w", stdout);

const int MAX_N = 1 + 200;

vector <int> G[MAX_N];
int risk[2][MAX_N];
int n, m, k;

void readData() {

    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &risk[0][i]);
    }
}

void getNextRisks() {

    for(int i = 1; i <= n; ++i)
        for(int j : G[i]) {
            risk[1][j] = max(risk[1][j], risk[0][i]);
        }
    for(int i = 1; i <= n; ++i)
        risk[0][i] = risk[1][i];
}

void cleanUp() {

    for(int i = 1; i <= n; ++i) {
        risk[1][i] = 0;
    }
}

void writeData() {

    for(int i = 1; i <= n; ++i) {
        printf("%d ", risk[0][i]);
    }
}

int main() {

    readData();
    for(int i = 1; i <= k; ++i) {
        getNextRisks();
        cleanUp();
    }
    writeData();
    return 0;
}
