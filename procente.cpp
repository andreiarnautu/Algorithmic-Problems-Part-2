/**
  *  Worg
  */
#include <cstdio>

#define MAX_N       1 + 80
#define MAX_P       1 + 200
#define inFile      "procente.in"
#define outFile     "procente.out"

using namespace std;

long long int dp[MAX_N * 2][MAX_N * 2][MAX_N];
int elem[MAX_P], p2[MAX_P], p5[MAX_P];
int N, p, A, B, pos;
char c;

void readData() {

    freopen(inFile, "r", stdin);
    scanf("%d %c %d", &N, &c, &p);
}

void getNumbers() {

    int x, f, t;
    for(int i = 1; i <= 200; ++i) {

        x = i;
        f = t = 0;
        while(!(x % 2))
            x /= 2, ++t;
        while(!(x % 5))
            x /= 5, ++f;

        if(x == 1)
            elem[++pos] = i, p2[pos] = t, p5[pos] = f;
    }
}

void knapsack() {

    if(c == '-')
        p = 100 - p;
    else
        p = 100 + p;
    A = N * 2, B = N * 2;
    while(!(p % 2))
        p /= 2, --A;
    while(!(p % 5))
        p /= 5, --B;
    if(p > 1)
        return;

    int t, f;
    dp[0][0][0] = 1;
    for(int it = 1; it <= pos; ++it) {

        t = p2[it];
        f = p5[it];
        for(int i = 0; i <= A - t; ++i)
            for(int j = 0; j <= B - f; ++j)
                for(int k = 0; k < N - 1; ++k)
                    dp[i + t][j + f][k + 1] += dp[i][j][k];
    }
}

void writeData() {

    freopen(outFile, "w", stdout);
    if(p > 1)
        printf("0");
    else
        printf("%lld", dp[A][B][N - 1]);
}

int main() {

    readData();
    getNumbers();
    knapsack();
    writeData();
    return 0;
}
