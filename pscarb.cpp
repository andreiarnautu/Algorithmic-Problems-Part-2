/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("pscarb.in", "r", stdin);
FILE *fout = freopen("pscarb.out", "w", stdout);

int N, K;

int main() {
    scanf("%d%d", &N, &K);
    if(K >= N || K >= 3) {
        printf("-1"); return 0;
    }
    if(N % 2 == 0) {
        printf("-1"); return 0;
    }

    for(int i = 1; i < N; ++i) {
        printf("%d %d\n", i, i + 1);
    }

    int X = 1;
    for(; 3 * X <= N; X += 2);
    X -= 2;


    for(int i = 1; i <= X; ++i) {
        printf("RGB");
    }
    if(N - 3 * X == 2) {
        printf("RR");
    }
    else if(N - 3 * X == 4) {
        printf("RRRR");
    }

    return 0;
}
