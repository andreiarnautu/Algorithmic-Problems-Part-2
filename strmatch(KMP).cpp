/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>

using std::vector;

FILE *fin = freopen("strmatch.in", "r", stdin);
FILE *fout = freopen("strmatch.out", "w", stdout);

const int kMaxN = 1 + 2000000;
const int kMaxOut = 1000;

/*-------- Input data --------*/
char A[kMaxN], B[kMaxN];
int len_A, len_B;
/*-------- KMP --------*/
int pi[kMaxN];

int solution;
vector<int > where;
/*-------- --------*/

void ReadInput() {
    scanf("%s%s", A + 1, B + 1);
    len_A = std::strlen(A + 1);
    len_B = std::strlen(B + 1);
}

void Prefix() {
    int k = 0;
    for(int i = 2; i <= len_A; i++) {
        while(k > 0 && A[i] != A[k + 1]) {
            k = pi[k];
        }
        if(A[i] == A[k + 1]) {
            k++;
        }
        pi[i] = k;
    }
}

void GetApparitions() {
    int k = 0;
    for(int i = 1; i <= len_B; i++) {
        while(k > 0 && B[i] != A[k + 1]) {
            k = pi[k];
        }
        if(B[i] == A[k + 1]) {
            k ++;
        }

        if(k == len_A) {
            solution ++;
            if(where.size() < kMaxOut) {
                where.push_back(i - len_A);
            }
        }
    }
}

void WriteOutput() {
    printf("%d\n", solution);
    for(int pos : where) {
        printf("%d ", pos);
    }
}

int main() {
    ReadInput();
    Prefix();
    GetApparitions();
    WriteOutput();

    return 0;
}
