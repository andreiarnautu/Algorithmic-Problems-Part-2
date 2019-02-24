/**
  *  Worg
  */
#include <stack>
#include <cstdio>
FILE *fin = freopen("sortnet.in", "r", stdin);
FILE *fout = freopen("sortnet.out", "w", stdout);

const int kMaxN = 20 + 1;
const int kMaxM = 32 + 1;

/*-------- Data --------*/
int N, M;
int swapPair[kMaxM][kMaxN];

int config[kMaxM][kMaxM];
int totalZeros;
std::stack<int > stack;
/*-------- --------*/


void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N / 2; j++) {
            int u, v; scanf(" <%d,%d>", &u, &v);
            swapPair[i][u] = v; swapPair[i][v] = u;
        }
    }
}

bool GetChanges(int x) {
    for(int i = 1; i <= M; i++) {
        int u = swapPair[i][x];
        int nextX = x;

        if((u < x && config[i - 1][u] == 1) || (x < u && config[i - 1][u] == 0)) {
            nextX = u;
        }
        config[i][nextX] = config[i - 1][x]; x = nextX;
    }
    for(int i = 1; i <= totalZeros; i++) {
        if(config[M][i] == 1) {
            return false;
        }
    }
    return true;
}

int GetValidConfigs() {
    int validConfigs = 1;
    for(int i = N; i >= 1; i--) {
        stack.push(i);
    }
    totalZeros = N;

    while(!stack.empty()) {
        int x = stack.top(); stack.pop();
        config[0][x] ^= 1;
        totalZeros += (config[0][x] == 0) ? 1 : -1;

        validConfigs += GetChanges(x);

        for(int i = x - 1; i >= 1; i--) {
            stack.push(i);
        }
    }

    return validConfigs;
}

int main() {
    ReadInput();
    printf("%d\n", GetValidConfigs());
    return 0;
}
