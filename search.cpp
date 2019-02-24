/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("search.in", "r", stdin);
FILE *fout = freopen("search.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_LEN = 1 + 5000 + 1;
const int SIGMA = 26;

/*-------------------------*/
int N, M;
int Len[MAX_N];
char Word[MAX_N][MAX_LEN];
/*-------------------------*/
int dp[MAX_N][MAX_LEN][SIGMA];

stack< int > Stack[MAX_N];
/*-------------------------*/


void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%s", Word[i] + 1);
        Len[i] = strlen(Word[i] + 1);
    }

}

void runDP() {
    for(int i = 1; i <= N; i++) {
        int crtLen = Len[i];
        for(int k = 0; k < SIGMA; k++) {
            dp[i][crtLen + 1][k] = crtLen + 1;
        }
        for(int j = crtLen; j >= 1; j--) {
            for(int k = 0; k < SIGMA; k++) {
                if(Word[i][j] == 'a' + k) {
                    dp[i][j][k] = j;
                } else {
                    dp[i][j][k] = dp[i][j + 1][k];
                }
            }
        }
    }
}

void solveQueries() {
    for(int i = 1; i <= N; i++) {
        Stack[i].push(0);
    }

    scanf(" ");
    for(; M > 0; M--) {
        char c; scanf("%c ", &c);

        if(c != '-') {
            for(int i = 1; i <= N; i++) {
                if(Stack[i].top() != Len[i] + 1) {
                    Stack[i].push(dp[i][Stack[i].top() + 1][c - 'a']);
                } else {
                    Stack[i].push(Len[i] + 1);
                }
            }
        } else {
            for(int i = 1; i <= N; i++) {
                Stack[i].pop();
            }
        }

        int Answer = 0;
        for(int i = 1; i <= N; i++) {
            if(Stack[i].top() != Len[i] + 1) {
                Answer++;
            }
         //   printf("%d; ", Stack[i].top());
        }
        printf("%d\n", Answer);
    }
}

int main() {
    readInput();
    runDP();
    solveQueries();
    return 0;
}
