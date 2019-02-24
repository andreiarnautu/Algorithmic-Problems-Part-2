/**
  *  Worg
  */
#include <string>
#include <fstream>
#include <utility>
#include <algorithm>

using namespace std;
ifstream fin("x.in");
ofstream fout("x.out");

const int MAX_N = (1 + 1000000) << 1;
const int MAX_Q = 1 + 500000;

/*-------- Input data --------*/
int N, M, Q;
string A, B;
pair< int,int > Queries[MAX_Q];
/*-------- Z-Algorithm --------*/
string S;
int Z[2][MAX_N];
/*-------- --------*/

void readInput() {
    fin >> M >> N >> Q;
    fin >> A >> B;
    for(int i = 1; i <= Q; i++) {
        fin >> Queries[i].first >> Queries[i].second;
    }
}

void runZ_Algorithm(int level) {
    int Size = M + N;
    int L = -1, R = -1;

    for(int i = 1; i < Size; i++) {
        if(i > R) {
            /* nu ne putem baza pe Z-Boxul anterior */
            if(S[0] == S[i]) {
                L = i;
                R = i - 1;

                for(int j = 0, k = i; k < Size && S[j] == S[k]; j++, k++) {
                    Z[level][i] ++;
                    R ++;
                }
            } else {
                Z[level][i] = 0;
            }
        } else {
            /* ne bazam pe Z-Boxul in care suntem */
            int before = i - L;
            if(Z[level][before] < R - i + 1) {
                Z[level][i] = Z[level][before];
            } else {
                Z[level][i] = R - i + 1;
                L = i;

                for(int before = Z[level][i]; R + 1 < Size && S[before] == S[R + 1]; before++, R++) {
                    Z[level][i] ++;
                }
            }
        }
    }
}

void solveQueries() {
    for(int i = 1; i <= Q; i++) {
        int x = Queries[i].first;
        int y = Queries[i].second;

        int maxAnswer = min(x - 1, M - y);

        int right = Z[0][N + y];
        int left = Z[1][M + N - x + 1];

        fout << min(maxAnswer, min(right, left)) << '\n';
    }
}

int main() {
    readInput();
    S = B + A; runZ_Algorithm(0);
    reverse(A.begin(), A.end());
    S = B + A; runZ_Algorithm(1);
    solveQueries();
    return 0;
}
