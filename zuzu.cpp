/**
  *  Worg
  */
#include <set>
#include <bitset>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::set;
using std::bitset;
using std::vector;

FILE *fin = freopen("zuzu.in", "r", stdin);
FILE *fout = freopen("zuzu.out", "w", stdout);

const int kMaxN = 1 + 40;
const int dx[] = {1, -1, 0,  0, 0,  0};
const int dy[] = {0,  0, 1, -1, 0,  0};
const int dz[] = {0,  0, 0,  0, 1, -1};

struct Parallelogram {
    double x[2], y[2], z[2];
    int direction;
    Parallelogram() {};
};

/*-------- Input data --------*/
int N, T;
Parallelogram parallelogram[kMaxN];
/*-------- Point sets --------*/
set<double > set_x, set_y, set_z;
vector<double > vec_x, vec_y, vec_z;
/*-------- Algorithm data --------*/
bitset< 2 * kMaxN > chosen[2 * kMaxN][2 * kMaxN];

double max_volume, crt_volume;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &T);
    for(int i = 1; i <= N; i++) {
        scanf("%lf%lf%lf%lf%lf%lf%d", &parallelogram[i].x[0], &parallelogram[i].y[0], &parallelogram[i].z[1], &parallelogram[i].x[1], &parallelogram[i].y[1], &parallelogram[i].z[0], &parallelogram[i].direction);
    }
}

void InsertPoints() {
    for(int i = 1; i <= N; i++) {
        set_x.insert(parallelogram[i].x[0]); set_x.insert(parallelogram[i].x[1]);
        set_y.insert(parallelogram[i].y[0]); set_y.insert(parallelogram[i].y[1]);
        set_z.insert(parallelogram[i].z[0]); set_z.insert(parallelogram[i].z[1]);
    }

    for(auto x : set_x) {
        vec_x.push_back(x);
    }
    for(auto y : set_y) {
        vec_y.push_back(y);
    }
    for(auto z : set_z) {
        vec_z.push_back(z);
    }
}

void ColorPieces(Parallelogram p) {
    int x1, x2, y1, y2, z1, z2;
    for(int i = 0; i < (int)vec_x.size(); i++) {
        if(p.x[0] == vec_x[i]) {
            x1 = i;
        }
        if(p.x[1] == vec_x[i]) {
            x2 = i;
        }
    }

    for(int i = 0; i < (int)vec_y.size(); i++) {
        if(p.y[0] == vec_y[i]) {
            y1 = i;
        }
        if(p.y[1] == vec_y[i]) {
            y2 = i;
        }
    }

    for(int i = 0; i < (int)vec_z.size(); i++) {
        if(p.z[0] == vec_z[i]) {
            z1 = i;
        }
        if(p.z[1] == vec_z[i]) {
            z2 = i;
        }
    }

    for(int i = x1; i < x2; i++) {
        for(int j = y1; j < y2; j++) {
            for(int k = z1; k < z2; k++) {
                chosen[i][j][k] = true;
            }
        }
    }
}

void ColorPieces() {
    for(int i = 1; i <= N; i++) {
        ColorPieces(parallelogram[i]);
    }
}

inline bool ValidPosition(int x, int y, int z) {
    return (0 <= x && 0 <= y && 0 <= z && x < (int)vec_x.size() - 1 && y < (int)vec_y.size() - 1 && z < (int)vec_z.size() - 1);
}

inline void Fill(int x, int y, int z) {
    crt_volume += (vec_x[x + 1] - vec_x[x]) * (vec_y[y + 1] - vec_y[y]) * (vec_z[z + 1] - vec_z[z]);
    chosen[x][y][z] = false;

    for(int i = 0; i < 6; i++) {
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        int z1 = z + dz[i];
        if(ValidPosition(x1, y1, z1) && chosen[x1][y1][z1]) {
            Fill(x1, y1, z1);
        }
    }
}

void GetCloudAreas() {
    max_volume = 0;
    for(int i = 0; i < (int)vec_x.size() - 1; i++) {
        for(int j = 0; j < (int)vec_y.size() - 1; j++) {
            for(int k = 0; k < (int)vec_z.size() - 1; k++) {
                if(chosen[i][j][k]) {
                    crt_volume = 0;
                    Fill(i, j, k);
                    max_volume = std::max(max_volume, crt_volume);
                }
            }
        }
    }
}

void GenerateNextStep() {
    for(int i = 1; i <= N; i++) {
        if(parallelogram[i].direction == 1) {
            parallelogram[i].x[0] ++; parallelogram[i].x[1] ++;
        } else if(parallelogram[i].direction == 2) {
            parallelogram[i].x[0] --; parallelogram[i].x[1] --;
        } else if(parallelogram[i].direction == 3) {
            parallelogram[i].y[0] ++; parallelogram[i].y[1] ++;
        } else if(parallelogram[i].direction == 4) {
            parallelogram[i].y[0] --; parallelogram[i].y[1] --;
        } else if(parallelogram[i].direction == 5) {
            parallelogram[i].z[0] ++; parallelogram[i].z[1] ++;
        } else {
            parallelogram[i].z[0] --; parallelogram[i].z[1] --;
        }
    }
}

void ClearData() {
    set_x.clear(); set_y.clear(); set_z.clear();
    vec_x.clear(); vec_y.clear(); vec_z.clear();
}

int main() {
    ReadInput();

    double solution = 0;
    int time = 0;
    for(int i = 0; i < T; i++) {
        InsertPoints();
        ColorPieces();
        GetCloudAreas();
        if(solution < max_volume) {
            solution = max_volume; time = i;
        }
        GenerateNextStep();
        ClearData();
    }

    printf("%d\n%d\n", (int)solution, time);
    return 0;
}
