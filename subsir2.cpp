/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("subsir2.in", "r", stdin);
FILE *fout = freopen("subsir2.out", "w", stdout);

const int MAX_N = 1 + 5000;
const int MAX_INF = 0x3ffffff;

/*--------------------*/
int V[MAX_N];
int N;
/*--------------------*/
int dp[MAX_N], nxt[MAX_N];
/*--------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &V[i]);
    }
}

void runDP() {
    for(int i = N; i >= 1; i--) {
        int minVal = MAX_INF;
        int index = 0;
        for(int j = i + 1; j <= N; j++) {
            if(V[j] < minVal && V[j] >= V[i]) {
                if(index == 0 || dp[j] <= dp[index]) {
                    index = j;
                }
                minVal = V[j];
            }
        }
        nxt[i] = index;
        dp[i] = dp[index] + 1;
    }
}

void writeData(int index) {
    printf("%d\n", dp[index]);
    while(index) {
        printf("%d ", index);
        index = nxt[index];
    }
}

void getSol() {
    int valMin = V[1];
    int index = 1;
    for(int i = 2; i <= N; i++) {
        if(V[i] < valMin) { /* verificam ca e maximal */
            if(dp[i] <= dp[index]) {
                index = i;
            }
            valMin = V[i];
        }
    }

    writeData(index);
}

int main() {
    readData();
    runDP();
    getSol();
    return 0;
}
