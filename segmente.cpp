/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("segmente.in", "r", stdin);
FILE *fout = freopen("segmente.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_INF = 1000000000;

struct Segment {
    int A, B, C;
    Segment(const int &A, const int &B, const int &C) {
        this->A = A; this->B = B; this->C = C;
    }
};
/*----------------*/
int N;
vector <Segment> orizontale, verticale;
/*----------------*/
int dp[MAX_N][MAX_N];
/*----------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

        if(x1 == x2) {
            if(y1 > y2) {
                swap(y1, y2);
            }
            verticale.push_back(Segment(x1, y1, y2));
        } else {
            if(x1 > x2) {
                swap(x1, x2);
            }
            orizontale.push_back(Segment(y1, x1, x2));
        }
    }
}

void runDP() {
    for(int i = 0; i < (int)orizontale.size(); ++i) {
        for(int j = 0; j < (int)verticale.size(); ++j) {
            Segment s1 = orizontale[i];
            Segment s2 = verticale[j];

            if(s1.B <= s2.A && s2.A <= s1.C) {
                if(s2.B <= s1.A && s1.A <= s2.C) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = min(abs(s2.C - s1.A), abs(s2.B - s1.A));
                }
            } else if(s2.B <= s1.A && s1.A <= s2.C) {
                dp[i][j] = min(abs(s1.C - s2.A), abs(s1.B - s2.A));
            } else {
                dp[i][j] = max(min(abs(s2.C - s1.A), abs(s2.B - s1.A)),
                               min(abs(s1.C - s2.A), abs(s1.B - s2.A)));
            }
        }
    }
}

void getSol() {
    int SOL = MAX_INF;
    if(orizontale.size() < verticale.size()) {
        for(int i = 0; i < (int)orizontale.size(); i++) {
            for(int j = i + 1; j < (int)orizontale.size(); ++j) {
                int min1 = MAX_INF;
                int min2 = MAX_INF;
                for(int k = 0; k < (int)verticale.size(); ++k) {
                    int d = max(dp[i][k], dp[j][k]);
                    if(d < min1) {
                        min2 = min1; min1 = d;
                    } else if (d < min2) {
                        min2 = d;
                    }
                }
                SOL = min(SOL, min2);
            }
        }
    } else {
        for(int i = 0; i < (int)verticale.size(); ++i) {
            for(int j = i + 1; j < (int)verticale.size(); ++j) {
                int min1 = MAX_INF;
                int min2 = MAX_INF;
                for(int k = 0; k < (int)orizontale.size(); ++k) {
                    int d = max(dp[k][i], dp[k][j]);
                    if(d < min1) {
                        min2 = min1; min1 = d;
                    } else if(d < min2) {
                        min2 = d;
                    }
                }
                SOL = min(SOL, min2);
            }
        }
    }

    printf("%d", SOL);
}

int main() {
    readData();
    runDP();
    getSol();
    return 0;
}
