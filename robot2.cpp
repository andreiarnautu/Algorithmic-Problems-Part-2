/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("robot2.in", "r", stdin);
FILE *fout = freopen("robot2.out", "w", stdout);

const int MAX_INF = 0x3fffffff;
const int MAX_N = 1 + 1000;
const int bufferDim = 100000;
const int dx[] = {-1, 1,  0, 0};
const int dy[] = { 0, 0, -1, 1};

class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*----------------------*/
int N, L1, L2, C1, C2;
bool mat[MAX_N][MAX_N];
/*----------------------*/
struct Object {
    int x, y, k;
    Object(const int x, const int y, const int k) {
        this->x = x; this->y = y; this->k = k;
    }
};

int dp[MAX_N][MAX_N][2][2];
bool inQueue[MAX_N][MAX_N][2];
bool ok[MAX_N][MAX_N];
queue <Object> Q;
/*----------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            int val; cin.getInt(val);
            mat[i][j] = (bool)val;
        }
    }
    cin.getInt(L1); cin.getInt(C1); cin.getInt(L2); cin.getInt(C2);
}

void Initialize(int index) {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            dp[i][j][0][index] = dp[i][j][1][index] = MAX_INF;
            inQueue[i][j][0] = inQueue[i][j][1] = false;
        }
    }
}

bool inMatrix(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= N && mat[x][y] == 0);
}

void Run(int index, int x0, int y0) { /* O(N * M) */
    Initialize(index);
    dp[x0][y0][0][index] = dp[x0][y0][1][index] = 0;
    Q.push(Object(x0, y0, 0)); Q.push(Object(x0, y0, 1));
    inQueue[x0][y0][0] = inQueue[x0][y0][1] = true;
    ok[x0][y0] = true;

    while(!Q.empty()) {
        Object current = Q.front(); Q.pop();
        int x = current.x;
        int y = current.y;
        int k = current.k;
        inQueue[x][y][k] = false;
        ok[x][y] = true;

        if(k == 0) {
            if(inMatrix(x, y - 1) && dp[x][y - 1][0][index] > dp[x][y][0][index]) {
                dp[x][y - 1][0][index] = dp[x][y][0][index];
                if(!inQueue[x][y - 1][0]) {
                    Q.push(Object(x, y - 1, 0)); inQueue[x][y - 1][0] = true;
                }
            } if(inMatrix(x, y + 1) && dp[x][y + 1][0][index] > dp[x][y][0][index]) {
                dp[x][y + 1][0][index] = dp[x][y][0][index];
                if(!inQueue[x][y + 1][0]) {
                    Q.push(Object(x, y + 1, 0)); inQueue[x][y + 1][0] = true;
                }
            } if(inMatrix(x - 1, y) && dp[x - 1][y][1][index] > dp[x][y][0][index] + 1) {
                dp[x - 1][y][1][index] = dp[x][y][0][index] + 1;
                if(!inQueue[x - 1][y][1]) {
                    Q.push(Object(x - 1, y, 1)); inQueue[x - 1][y][1] = true;
                }
            } if(inMatrix(x + 1, y) && dp[x + 1][y][1][index] > dp[x][y][0][index] + 1) {
                dp[x + 1][y][1][index] = dp[x][y][0][index] + 1;
                if(!inQueue[x + 1][y][1]) {
                    Q.push(Object(x + 1, y, 1)); inQueue[x + 1][y][1] = true;
                }
            }
        } else {
            if(inMatrix(x - 1, y) && dp[x - 1][y][1][index] > dp[x][y][1][index]) {
                dp[x - 1][y][1][index] = dp[x][y][1][index];
                if(!inQueue[x - 1][y][1]) {
                    Q.push(Object(x - 1, y, 1)); inQueue[x - 1][y][1] = true;
                }
            } if(inMatrix(x + 1, y) && dp[x + 1][y][1][index] > dp[x][y][1][index]) {
                dp[x + 1][y][1][index] = dp[x][y][1][index];
                if(!inQueue[x + 1][y][1]) {
                    Q.push(Object(x + 1, y, 1)); inQueue[x + 1][y][1] = true;
                }
            } if(inMatrix(x, y - 1) && dp[x][y - 1][0][index] > dp[x][y][1][index] + 1) {
                dp[x][y - 1][0][index] = dp[x][y][1][index] + 1;
                if(!inQueue[x][y - 1][0]) {
                    Q.push(Object(x, y - 1, 0)); inQueue[x][y - 1][0] = true;
                }
            } if(inMatrix(x, y + 1) && dp[x][y + 1][0][index] > dp[x][y][1][index] + 1) {
                dp[x][y + 1][0][index] = dp[x][y][1][index] + 1;
                if(!inQueue[x][y + 1][0]) {
                    Q.push(Object(x, y + 1, 0)); inQueue[x][y + 1][0] = true;
                }
            }
        }
    }
}

int changes;

void taskOne() {
    changes = min(dp[L2][C2][0][0], dp[L2][C2][1][0]);
    printf("%d ", changes);
}

int Try(int x1, int y1, int x2, int y2, int p = 1, int q = 1) {
    int answer = changes;
    int A1 = dp[x1][y1][0][0];
    int A2 = dp[x1][y1][1][0];
    int A3 = dp[x2][y2][1][1];
    int A4 = dp[x2][y2][0][1];

    int B1 = dp[x1][y1][0][1];
    int B2 = dp[x1][y1][1][1];
    int B3 = dp[x2][y2][1][0];
    int B4 = dp[x2][y2][0][0];

    if(y1 == y2) {
        answer = min(answer, A2 + A3);
        answer = min(answer, B2 + B3);
        answer = min(answer, A2 + A4 + 1);
        answer = min(answer, B2 + B4 + 1);
        answer = min(answer, A1 + A3 + 1);
        answer = min(answer, B1 + B3 + 1);
        answer = min(answer, A1 + A4 + 2);
        answer = min(answer, B2 + B4 + 2);
    } else if(x1 == x2) {
        answer = min(answer, A1 + A4);
        answer = min(answer, B1 + B4);
        answer = min(answer, A2 + A4 + 1);
        answer = min(answer, B2 + B4 + 1);
        answer = min(answer, A1 + A3 + 1);
        answer = min(answer, B1 + B3 + 1);
        answer = min(answer, A2 + A3 + 2);
        answer = min(answer, B2 + B3 + 2);
    } else if(p == 1) {
        answer = min(answer, A2 + A4 + 1);
        answer = min(answer, B2 + B4 + 1);
        answer = min(answer, A2 + A3 + 2);
        answer = min(answer, B2 + B3 + 2);
        answer = min(answer, A1 + A4 + 2);
        answer = min(answer, B1 + B4 + 2);
        answer = min(answer, A1 + A3 + 3);
        answer = min(answer, B1 + B3 + 3);
    } else if(q == 4) {
        answer = min(answer, A1 + A3 + 1);
        answer = min(answer, B1 + B3 + 1);
        answer = min(answer, A2 + A3 + 2);
        answer = min(answer, B2 + B3 + 2);
        answer = min(answer, A1 + A4 + 2);
        answer = min(answer, B2 + B4 + 2);
        answer = min(answer, A2 + A4 + 3);
        answer = min(answer, B2 + B4 + 3);
    }

    return answer;
}

void taskTwo() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(!mat[i][j]) {
                if(dp[i][j][0][0] == MAX_INF && dp[i][j][1][0] != MAX_INF) {
                    dp[i][j][0][0] = dp[i][j][1][0] + 1;
                }
                if(dp[i][j][1][0] == MAX_INF && dp[i][j][0][0] != MAX_INF) {
                    dp[i][j][1][0] = dp[i][j][0][0] + 1;
                }
                if(dp[i][j][0][1] == MAX_INF && dp[i][j][1][1] != MAX_INF) {
                    dp[i][j][0][1] = dp[i][j][1][1] + 1;
                }
                if(dp[i][j][1][1] == MAX_INF && dp[i][j][0][1] != MAX_INF) {
                    dp[i][j][1][1] = dp[i][j][0][1] + 1;
                }
            }
        }
    }


    int best = changes;
    int cnt = 0;

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(mat[i][j] == 1) {
                int current = changes;
                if(inMatrix(i - 1, j)) {
                    if(inMatrix(i, j - 1)) {
                        int val = Try(i - 1, j, i, j - 1, 1, 2);
                        current = min(current, val);
                    }
                    if(inMatrix(i, j + 1)) {
                        int val = Try(i - 1, j, i, j + 1, 1, 3);
                        current = min(current, val);
                    }
                    if(inMatrix(i + 1, j)) {
                        int val = Try(i - 1, j, i + 1, j);
                        current = min(current, val);
                    }
                }
                if(inMatrix(i, j - 1)) {
                    if(inMatrix(i, j + 1)) {
                        int val = Try(i, j - 1, i, j + 1);
                        current = min(current, val);
                    }
                    if(inMatrix(i + 1, j)) {
                        int val = Try(i, j - 1, i + 1, j, 2, 4);
                        current = min(current, val);
                    }
                }
                if(inMatrix(i, j + 1)) {
                    if(inMatrix(i + 1, j)) {
                        int val = Try(i, j + 1, i + 1, j, 3, 4);
                        current = min(current, val);
                    }
                }
                if(current == best) {
                    cnt++;
                } else if(current < best) {
                    best = current; cnt = 1;
                }
            }
        }
    }

    printf("%d %d\n", best, cnt);
}

int main() {
    readData();
    Run(0, L1, C1);
    Run(1, L2, C2);
    taskOne();
    taskTwo();
    return 0;
}
