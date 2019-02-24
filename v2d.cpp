/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("v2d.in", "r", stdin);
FILE *fout = freopen("v2d.out", "w", stdout);

const int MAX_N = 1 + 500;
const int MAX_T = 1 + 50;
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};
/*----------------------------------------*/
int now[MAX_N][MAX_N], nxt[MAX_N][MAX_N];
int N, T, Q;
/*----------------------------------------*/
queue< pair<int,int> > q;
/*----------------------------------------*/

void readData() {
    scanf("%d%d%d", &N, &T, &Q);
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            scanf("%d", &now[i][j]);
        }
    }
}

void initNext() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            nxt[i][j] = -MAX_T;
        }
    }
}

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void Try(int x1, int y1) {
    q.push(make_pair(x1, y1));
    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if(1 <= newX && newX <= N && 1 <= newY && newY <= N && nxt[newX][newY] < nxt[x1][y1] - dist(x1, y1, newX, newY)) {
                if(x1 == newX && y1 == newY) {
                    continue;
                } else {
                    nxt[newX][newY] = nxt[x1][y1] - dist(x1, y1, newX, newY);
                    q.push(make_pair(newX, newY));
                }
            }
        }
    }
}

void getNext() {
    for(int x = 1; x <= N; ++x) {
        for(int y = 1; y <= N; ++y) {
            for(int i = 0; i < 4; ++i) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if(1 <= newX && newX <= N && 1 <= newY && newY <= N) {
                    nxt[x][y] = max(nxt[x][y], now[newX][newY] - 1);
                }
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            Try(i, j);
        }
    }
}

void changeMatrix(int z) {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            now[i][j] = z + 1 + ((now[i][j] + z * nxt[i][j]) % Q);
        }
    }
}

int main() {
    readData();
    for(int i = 1; i <= T; ++i) {
        initNext();
        getNext();
        changeMatrix(i);
    }

    int SOL = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            SOL = (SOL + now[i][j]) % Q;
        }
    }
    printf("%d", SOL);
    return 0;
}
