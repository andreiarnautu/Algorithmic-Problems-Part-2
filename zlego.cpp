/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("zlego.in", "r", stdin);
FILE *fout = freopen("zlego.out", "w", stdout);

const int MAX_N = 1 + 250000;

int N;
int height[MAX_N];
long long coef[MAX_N];
int pi[MAX_N];

void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &height[i]);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%lld", &coef[i]);
    }
}

void makePi() {
    int k = 0;
    for(int i = 2; i <= N; i++) {
        while(k > 0 && height[i] != height[k + 1]) {
            k = pi[k];
        }
        if(height[i] == height[k + 1]) {
            k++;
        }
        pi[i] = k;
    }
}

void writeOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%lld\n", coef[i]);
    }
}

int main() {
    int T;
    for(scanf("%d", &T); T; T--) {
        readInput();
        makePi();
        for(int i = N; i > 1; i--) {
            coef[pi[i]] += coef[i];
        }
        writeOutput();
    }
    return 0;
}
