/**
  *  Worg
  */
#include <cstdio>
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

long long FirstTask() {
    long long K, X; scanf("%lld%lld", &K, &X);
    long long line = ((X - 1) >> K) + 1;
    long long col = ((X - 1) & ((1LL << K) - 1)) + 1;
    long long numberHeight = 1, normalHeight = 1;
    long long size = (1LL << K);

    while(K > 0) {
        //printf("%lld %lld; -> ", line, col);
        ///  Step one
        if(line > (size >> 1)) {
            numberHeight = (normalHeight - numberHeight + 1) + normalHeight;
            line = size - line + 1;
        }
        normalHeight <<= 1;
        ///  Step two
        if(col > (size >> 1)) {
            numberHeight = (normalHeight - numberHeight + 1) + normalHeight;
            col = size - col + 1;
        }
        normalHeight <<= 1;

        size >>= 1; K--;
    }

    return numberHeight;
}

long long SecondTask() {
    long long K, P; scanf("%lld %lld", &K, &P);
    long long line = 1, col = 1;
    long long numberHeight = P, normalHeight = (1LL << (2 * K));
    long long size = 1;

    while(normalHeight != 1) {
        ///  Step one
        if(numberHeight > (normalHeight >> 1)) {
            numberHeight = normalHeight - numberHeight + 1;
            col = size * 2 - col + 1;
        }
        normalHeight >>= 1;
        ///  Step two
        if(numberHeight > (normalHeight >> 1)) {
            numberHeight = normalHeight - numberHeight + 1;
            line = size * 2 - line + 1;
        }
        normalHeight >>= 1;

        size <<= 1;
    }

    long long number = (line - 1) * (1LL << K) + col;
    return number;
}

int main() {
    int Q;
    for(scanf("%d", &Q); Q > 0; Q--) {
        int type; scanf("%d", &type);
        if(type == 1) {
            printf("%lld\n", FirstTask());
        } else {
            printf("%lld\n", SecondTask());
        }
    }
    return 0;
}
