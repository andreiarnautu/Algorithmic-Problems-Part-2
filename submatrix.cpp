/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("submatrix.in", "r", stdin);
FILE *fout = freopen("submatrix.out", "w", stdout);

const int MAX_N = 1 + 300;

/*-----------------------*/
int N, M, K;
int mat[MAX_N][MAX_N];
/*-----------------------*/
unordered_map< int,int > Map;
int distinctCount;

int freq[MAX_N * MAX_N];
int maxIndex;
/*-----------------------*/

void readInput() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void normalizeData() {
    int crtIndex = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(Map.find(mat[i][j]) == Map.end()) {
                Map[mat[i][j]] = (++crtIndex);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            mat[i][j] = Map[mat[i][j]];
        }
    }
    maxIndex = crtIndex;

}

void Insert(int value) {
    if(!freq[value]) {
        distinctCount++;
    }
    freq[value]++;
}

void Remove(int value) {
    freq[value]--;
    if(!freq[value]) {
        distinctCount--;
    }
}

void solveProblem() {
    int startX = 1;
    int startY = M;

    int Answer = 0;

    while(startX != N + 1 || startY != 1) {
        pair< int,int > Up = make_pair(startX, startY);
        pair< int,int > Down = make_pair(startX, startY);

        int crtSize = 0;

        while(Down.first <= N && Down.second <= M) {
            for(int line = Up.first; line <= Down.first; line++) {
                Insert(mat[line][Down.second]);
            }
            for(int col = Up.second; col <= Down.second; col++) {
                Insert(mat[Down.first][col]);
            }

            crtSize++;

            while(distinctCount > K) {
                for(int line = Up.first; line <= Down.first; line++) {
                    Remove(mat[line][Up.second]);
                }
                for(int col = Up.second; col <= Down.second; col++) {
                    Remove(mat[Up.first][col]);
                }

                crtSize--;
                Up.first++; Up.second++;
            }

            Answer = max(Answer, crtSize);
            Down.first++; Down.second++;
        }

        Down.first--; Down.second--;

        for(int i = 1; i <= maxIndex; i++) {
            freq[i] = 0;
        }
        distinctCount = 0;

        if(startY > 1) {
            startY--;
        } else {
            startX++;
        }
    }

    printf("%d\n", Answer);
}

int main() {
    readInput();
    normalizeData();
    solveProblem();
    return 0;
}
