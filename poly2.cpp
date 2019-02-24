/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("poly2.in", "r", stdin);
FILE *fout = freopen("poly2.out", "w", stdout);

const int MOD = 30103;
const int MAX_N = 1 + 500;

int cat[MAX_N];
int N;

void readData() {
    scanf("%d", &N);
}

void getCatalan() {
    cat[0] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = 0; j < N; ++j) {
            cat[i] = (cat[i] + (cat[j] * cat[i - j - 1])) % MOD;
        }
    }
}

void writeData() {
    printf("%d", cat[N]);
}

int main() {
    readData();
    getCatalan();
    writeData();
    return 0;
}
