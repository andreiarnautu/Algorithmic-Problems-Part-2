/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("vis.in", "r", stdin);
FILE *fout = freopen("vis.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int INF = 50000000;
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

int m[MAX_N][MAX_N];
int N, K1, K2, L1, C1, L2, C2;

queue < pair<int,int> > q;
int dist[MAX_N][MAX_N];
int d[10];

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(K1); cin.getInt(K2); cin.getInt(L1); cin.getInt(C1); cin.getInt(L2); cin.getInt(C2);

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin.getInt(m[i][j]);
        }
    }
}

bool inTheMatrix(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= N);
}

void resetMatrix() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            dist[i][j] = -1;
        }
    }
}

void matrixBFS(int xStart, int yStart, int low, int high) {
    dist[xStart][yStart] = 1;
    q.push(make_pair(xStart, yStart));

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if(inTheMatrix(newX, newY) && dist[newX][newY] == -1 && (m[newX][newY] <= low || m[newX][newY] >= high)) {
                dist[newX][newY] = dist[x][y] + 1;
                q.push(make_pair(newX, newY));
            }
        }
    }
}

void calc11() {
    resetMatrix();
    matrixBFS(1, 1, 0, INF);
    d[1] = dist[L1][C1];
    d[2] = dist[L2][C2];
    d[3] = dist[N][N];
    resetMatrix();
}

void calcL1C1() {
    matrixBFS(L1, C1, K1, INF);
    d[4] = dist[N][N];
    d[5] = dist[L2][C2];
    resetMatrix();

    matrixBFS(L1, C1, K1, K2);
    d[6] = dist[N][N];
    resetMatrix();
}

void calcL2C2() {
    matrixBFS(L2, C2, 0, K2);
    d[7] = dist[N][N];
    d[8] = dist[L1][C1];
    resetMatrix();

    matrixBFS(L2, C2, K1, K2);
    d[9] = dist[N][N];
    resetMatrix();
}

void writeData() {
    int answer = INF;
    answer = min(answer, d[3]);
    answer = min(answer, d[1] + d[4] - 1);
    answer = min(answer, d[2] + d[7] - 1);
    answer = min(answer, d[1] + d[5] + d[9] - 2);
    answer = min(answer, d[2] + d[8] + d[6] - 2);

    printf("%d", answer);
}

int main() {
    readData();
    calc11();
    calcL1C1();
    calcL2C2();
    for(int i = 1; i <= 9; ++i) {
        if(d[i] == -1) {
            d[i] = INF;
        }
    }
    writeData();
    return 0;
}
