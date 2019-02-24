/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("volum.in", "r", stdin);
FILE *fout = freopen("volum.out", "w", stdout);

const int MAX_N = 1 + 752;
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};

struct Cell {
    int x, y;
    int height;

    Cell(const int x, const int y, const int height) {
        this->x = x; this->y = y; this->height = height;
    }

    bool operator <(const Cell &other) const {
        return this->height < other.height;
    }
};

/*--------------------*/
int N, M;
int mat[MAX_N][MAX_N];
/*--------------------*/
bool checked[MAX_N][MAX_N];
multiset< Cell > Set;
/*--------------------*/
long long Solution;

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void addNewCell(int x, int y, int height) {
    if(checked[x][y]) {
        return;
    } else {
        checked[x][y] = true;
    }

    Solution += 1LL * max(height - mat[x][y], 0);

    Set.insert(Cell(x, y, max(height, mat[x][y])));
}

bool inTheMatrix(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= M);
}

void solveProblem() {
    /* first we introduce the edges */
    for(int i = 1; i <= N; i++) {
        addNewCell(i, 1, mat[i][1]);
        addNewCell(i, M, mat[i][M]);
    }

    for(int j = 1; j <= M; j++) {
        addNewCell(1, j, mat[1][j]);
        addNewCell(N, j, mat[N][j]);
    }

    while(!Set.empty()) {
        Cell cell = *Set.begin(); Set.erase(Set.begin());

        for(int i = 0; i < 4; i++) {
            int x = cell.x + dx[i];
            int y = cell.y + dy[i];
            if(inTheMatrix(x, y)) {
                addNewCell(x, y, cell.height);
            }
        }
    }
}

void writeOutput() {
    printf("%lld\n", Solution);
}

int main() {
    readInput();
    solveProblem();
    writeOutput();

    return 0;
}
