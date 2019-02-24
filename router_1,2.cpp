/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("router.in", "r", stdin);
FILE *fout = freopen("router.out", "w", stdout);

int main() {
    int N; scanf("%d", &N);
    printf("%d %d\n", 2 * N, N * N);
    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= 2 * N; j++) {
            printf("%d %d\n", i, j);
        }
    }
}
