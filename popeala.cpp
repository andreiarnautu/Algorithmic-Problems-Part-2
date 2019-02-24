/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("popeala.in", "r", stdin);
FILE *fout = freopen("popeala.out", "w", stdout);

const int MAX_N = 1 + 50;
const int MAX_T = 1 + 20000;
const int T_PARTIAL = 1 + 4000;
const int MAX_S = 1 + 50;
const int MAX_INF = 2000000000;

/*---------------------------*/
int N, T, S;
int Points[MAX_T];
bool Results[MAX_N][MAX_T];
char binString[MAX_T];
/*---------------------------*/
int zeroCount[MAX_N][MAX_T];
int partialPoints[MAX_T];
int subtask[T_PARTIAL][T_PARTIAL];
int dp[MAX_T][MAX_S];
/*---------------------------*/


void readData() {
    scanf("%d%d%d", &N, &T, &S);

    for(int i = 1; i <= T; i++) {
        scanf("%d", &Points[i]);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%s", binString);
        for(int j = 1; j <= T; j++) {
            if(binString[j - 1] == '1') {
                Results[i][j] = true;
            }
        }
    }
}


int subtaskValue(int left, int right) {
    int answer = 0;
    for(int i = 1; i <= N; i++) {
        if(zeroCount[i][right] == zeroCount[i][left - 1]) {
            answer += partialPoints[right] - partialPoints[left - 1];
        }
    }
    return answer;
}


void preCalc() {
    /* computing zeroCount */

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= T; j++) {
            zeroCount[i][j] = zeroCount[i][j - 1] + (Results[i][j] == 0);
        }
    }

    for(int i = 1; i <= T; i++) {
        partialPoints[i] = partialPoints[i - 1] + Points[i];
    }

    for(int i = 1; i <= T; i++) {
        for(int j = i; j <= T; j++) {
            subtask[i][j] = subtaskValue(i, j);
        }
    }
}

void runDP() {

    for(int i = 1; i <= T; i++) {
        dp[i][1] = subtaskValue(1, i);
    }

    for(int j = 2; j <= S; j++) {
        for(int i = j; i <= T; i++) {
            /* we compute the value of dp[i][j] */

            dp[i][j] = MAX_INF;

            for(int w = i - 1; w >= j - 1; w--) {
                dp[i][j] = min(dp[i][j], dp[w][j - 1] + subtask[w + 1][i]);
            }
        }
    }
}

void writeData() {
    for(int i = 1; i <= S; i++) {
        printf("%d\n", dp[T][i]);
    }
}

int main() {
    readData();
    preCalc();
    runDP();
    writeData();
    return 0;
}
