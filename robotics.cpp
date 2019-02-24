/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("robotics.in", "r", stdin);
FILE *fout = freopen("robotics.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_INF = 1000000;

int N, M, T;

vector <int> D1[2 * MAX_N];
vector <int> D2[2 * MAX_N];

void readData() {
    scanf("%d%d%d", &N, &M, &T);

    int answer = 0;
    for(int i = 1; i <= M; ++i) {
        int x, y, type; scanf("%d%d%d", &x, &y, &type);
        if(type == 1) {
            answer += min(T, min(x - 1, N - y));
            answer += min(T, min(N - x, y - 1));
            D1[x + y].push_back(x);
        }
        else {
            answer += min(T, min(x - 1, y - 1));
            answer += min(T, min(N - x, N - y));
            D2[x - y + N].push_back(x);
        }
        answer++;
    }
    printf("%d\n", answer);
}

void solveSecond() {
    int answer = MAX_INF;

    for(int d2 = 2; d2 <= 2 * N; d2 += 2) {
        if(D2[d2].size()) {
            for(int d2Prim = d2 + 2; d2Prim <= 2 * N; d2 += 2) {
                if(D2[d2Prim].size()) {
                    for(int d1 = 2; d1 < 2 * N; d1 += 2) {
                        if(D1[d1].size()) {
                            for(int d1Prim = d1 + 2; d1Prim < 2 * N; d1Prim += 2) {
                                if(D1[d1Prim].size()) {
                                    int currentT = 0, x;
                                    x = (d1 + d2) / 2;
                                    currentT = max(currentT, abs(D1[d1] - x))
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    readData();
    solveSecond();

    return 0;
}
