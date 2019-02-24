/**
  *  Worg
  */
#include <set>
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("zone2.in", "r", stdin);
FILE *fout = freopen("zone2.out", "w", stdout);

const int dx[] = {-1, 1,  0, 0};
const int dy[] = { 0, 0, -1, 1};
const int MAX_N = 1 + 300 + 1;
const int MAX_ZONES = MAX_N * MAX_N;

/*-----------------------*/
char mat[MAX_N][MAX_N];
int N, M, K;
/*-----------------------*/
int zone[MAX_N][MAX_N];
int Size[MAX_ZONES], degree[MAX_ZONES];
int zoneCount;
vector <int> G[MAX_ZONES];
set <int> Set;
/*-----------------------*/
queue <int> q;
/*-----------------------*/

void readData() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 1; i <= N; ++i) {
        scanf("%s", mat[i] + 1);
    }
}

bool inTheMatrix(int x, int y) {
    return(1 <= x && x <= N && 1 <= y && y <= M);
}

void Fill(int x, int y) {
    Size[zoneCount]++;
    zone[x][y] = zoneCount;
    for(int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if(inTheMatrix(newX, newY) && mat[x][y] == mat[newX][newY] && !zone[newX][newY]) {
            Fill(newX, newY);
        }
        else if(zone[newX][newY] && mat[x][y] != mat[newX][newY]) {
            if(Set.find(zone[newX][newY]) == Set.end()) {
                Set.insert(zone[newX][newY]);
            }
        }
    }

}

void getAreas() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            if(!zone[i][j]) {
                zoneCount++;
                Fill(i, j);
                for(set <int>::iterator it = Set.begin(); it != Set.end(); ++it) {
                    G[*it].push_back(zoneCount);
                    G[zoneCount].push_back(*it);
                    degree[*it]++; degree[zoneCount]++;
                }
                Set.clear();
            }
        }
    }
}

void getSuperZone() {
    int answer = M * N;
    for(int i = 1; i <= zoneCount; ++i) {
        if(degree[i] < K) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int current = q.front(); q.pop();
        answer -= Size[current];

        for(vector <int>::iterator it = G[current].begin(); it != G[current].end(); ++it) {
            degree[*it]--;
            if(degree[*it] == K - 1) {
                q.push(*it);
            }
        }
    }

    printf("%d", answer);
}

int main() {
    readData();
    getAreas();
    getSuperZone();
    return 0;
}
