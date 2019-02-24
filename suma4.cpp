/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("suma4.in", "r", stdin);
FILE *fout = freopen("suma4.out", "w", stdout);

const int MAX_L = 60;
const int MAX_N = 65000;

int n;
int vec[MAX_N];

int L;
int a[MAX_L][MAX_L][MAX_L], dp[MAX_L][MAX_L][MAX_L], index[MAX_L][MAX_L][MAX_L];

void readData() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &vec[i]);
    }
}

void buildMatrix() {
    int pos = 1;
    for(int i = 1; n != 0; n -= i * i, i++, L++) {
        for(int lat = 1; lat <= i; ++lat) {
            for(int col = 1; col <= i; ++col) {
                index[i][lat][col] = pos;
                a[i][lat][col] = vec[pos++];
            }
        }
    }
}

void runDP() {
    for(int i = 1; i <= L; ++i) {
        for(int j = 1; j <= L; ++j) {
            dp[L][i][j] = a[L][i][j];
        }
    }

    for(int i = L - 1; i > 0; --i) {
        for(int lat = 1; lat <= i; lat++) {
            for(int col = 1; col <= i; ++col) {
                dp[i][lat][col] = a[i][lat][col] +
                                  min(min(dp[i + 1][lat][col], dp[i + 1][lat + 1][col]),
                                      min(dp[i + 1][lat + 1][col + 1], dp[i + 1][lat][col + 1]));
            }
        }
    }
}

void getPath() {
    int i = 1, j = 1;
    for(int level = 1; level < L; ++level) {
        printf("%d ", index[level][i][j]);
        if(dp[level][i][j] - dp[level + 1][i][j] == a[level][i][j]) {
            continue;
        }
        if(dp[level][i][j] - dp[level + 1][i][j + 1] == a[level][i][j]) {
            j++;
            continue;
        }
        if(dp[level][i][j] - dp[level + 1][i + 1][j] == a[level][i][j]) {
            i++;
            continue;
        }
        if(dp[level][i][j] - dp[level + 1][i + 1][j + 1] == a[level][i][j]) {
            i++, j++;
            continue;
        }
    }
    printf("%d", index[L][i][j]);
}

void writeData() {
    printf("%d %d\n", L, dp[1][1][1]);
    getPath();
}

int main() {
    readData();
    buildMatrix();
    runDP();
    writeData();
    return 0;
}
