/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX_N = 1 + 100000;
const int MAX_LOG = 20;

int n;
int vec[MAX_N];
int lg[MAX_N];

int RMQ[MAX_LOG][2 * MAX_N];

void readData() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &vec[i]);
    }
}

void makeRMQ() {
    for(int i = 2; i <= n; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }


    for(int i = 0; i <= 19; ++i)
        for(int j = 0; j <= 200000; ++j)
            RMQ[i][j] = -(1 << 31);

    for(int i = 1; i <= n; ++i) {
        RMQ[0][i] = vec[i];
    }

    for(int i = 1; (1 << i) <= n ; ++i) {
        for(int j = 1; j <= n; ++j) {
            RMQ[i][j] = max(RMQ[i - 1][j], RMQ[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int queryRMQ(int a, int b) {
    int level = lg[b - a + 1];
    return max(RMQ[level][a], RMQ[level][b - (1 << level) + 1]);
}

int main() {
    readData();
    makeRMQ();

    int answer = -(1 << 31);
    for(int i = 1; i <= n; ++i)
        for(int j = 0; i + (1 << j) <= n; ++j) {
            int current = vec[i] + queryRMQ(i + (1 << j), i + (1 << (j + 1)) - 1) - j;
           // printf("%d %d %d\n", i, j, queryRMQ(i + (1 << j), i + (1 << (j + 1)) - 1));
            //queryRMQ(i + (1 << j), i + (1 << (j + 1)) - 1)
          //  printf("%d %d %d\n", i, j, current);
            answer = max(answer, current);
        }
    printf("%d", answer);
    return 0;
}
