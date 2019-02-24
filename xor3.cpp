/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("xor3.in", "r", stdin);
FILE *fout = freopen("xor3.out", "w", stdout);

int Q, i, j, a, b, m;

int main() {
    scanf("%d%d%d%d%d%d", &Q, &i, &j, &a, &b, &m);

    for(; Q; Q--) {
        int Answer = 0;
        for(int exp = 0, pow = 1; pow <= j; pow <<= 1, exp++) {
            Answer |= (((i + pow) & (j - pow)) == 0) << exp;
        }
        printf("%d\n", Answer);

        i = (a * i + b) % m;
        j = (a * j + b) % m;
    }

    return 0;
}
