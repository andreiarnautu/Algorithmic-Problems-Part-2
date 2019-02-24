/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("weeee.in", "r", stdin);
FILE *fout = freopen("weeee.out", "w", stdout);

const int MAX_N = 1 + 200000 + 10;
const long long MAX_INF = 1000000000000000;
/*----------------*/
int N;
char s[MAX_N];
/*----------------*/
int pos[MAX_N];
int k;
/*----------------*/
bool foundW, foundE;

void readData() {
    scanf("%d%s", &N, s + 1);
}

void getPos() {
    for(int i = 1; i <= N; ++i) {
        if(s[i] == 'W') {
            pos[++k] = i;
        }
    }
}

void solveProblem() {
    /* incepem prin a presupune ca avem toti W stransi in stanga */
    long long answer = MAX_INF;
    long long current = 0;

    for(int i = 1; i <= k; ++i) {
        current += 1LL * pos[i] - 1LL * i;
    }
    answer = min(answer, current);

    for(int i = k; i >= 1; --i) {
        current += 1LL * i - 1LL * pos[i];
        /* ducem elementul in pozitia N - (k - i) */
        int nxtPos = N - k + i;
        current += 1LL * nxtPos - 1LL * pos[i];

        answer = min(answer, current);
    }

    printf("%lld", answer);
}

int main() {
    readData();
    for(int i = 1; i <= N; ++i) {
        if(s[i] == 'W') {
            foundW = true;
        }
        if(s[i] == 'E') {
            foundE = true;
        }
    }
    if(!foundE || !foundW) {
        printf("-1"); return 0;
    }

    getPos();
    solveProblem();
}
