/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("urat.in", "r", stdin);
FILE *fout = freopen("urat.out", "w", stdout);

const long long MOD = 543217;

int N;

void Task_2() {
    long long fact = 1;
    int K = N >> 1;
    for(int i = 2; i < K; i++) {
        fact = (fact * i) % MOD;
    }

    if(N % 2 == 0) {
        printf("%lld\n", (fact * fact * 2) % MOD);
    } else {
        printf("%lld\n", (fact * fact * (K) * 4) % MOD);
    }
}

void Task_3() {
    int K = N >> 1;
    printf("%d ", K);

    for(int i = K + 2, j = 1; i <= 2 * K; i++, j++) {
        printf("%d %d ", i, j);
    }

    if(N % 2 == 1) {
        printf("%d ", N);
    }
    printf("%d ", K + 1);
}

int main() {
    scanf("%d", &N);

    printf("%lld\n", 1LL * N * N / 2 - 1); /* Task 1 */

    Task_2();
    Task_3();
    return 0;
}
