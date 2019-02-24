/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("sirag2.in", "r", stdin);
FILE *fout = freopen("sirag2.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*--------------------*/
int N, L;
char S[MAX_N];
/*--------------------*/
int dp[MAX_N];
vector< int > Lists[MAX_N];

deque< int > Deque;
/*--------------------*/

void readInput() {
    scanf("%d%d", &N, &L);
    scanf("%s", S + 1);

    for(int i = 1; i <= N; i++) {
        dp[i] = 1;
    }
}

void runDP(const vector< int > &vec) {
    int last = -1;
    for(int i = 0; i < (int)vec.size(); i++) {
        const int index = vec[i];
        if(S[index] == '*') {
            dp[index] = i - last;
            if(last != -1) {
                dp[index] += dp[vec[last]];
            }
        } else {
            if(last == -1) {
                dp[index] = i - last;
            } else if(S[index] == S[vec[last]]){
                dp[index] = dp[vec[last]] + i - last;
            } else {
                dp[index] = i - last;
            }
            last = i;
        }
    }
}

void makeLists() {
    for(int i = 1; i <= N; i++) {
        Lists[i % L].push_back(i);
    }
    for(int i = 0; i < L; i++) {
        runDP(Lists[i]);
        Lists[i].clear();
    }
}

int getAnswer() {
    int Answer = 0;

    for(int i = 1; i <= N; i++) {
        while(!Deque.empty() && dp[i] <= dp[Deque.back()]) {
            Deque.pop_back();
        }
        Deque.push_back(i);
        if(Deque.front() == i - L) {
            Deque.pop_front();
        }

        if(i >= L) {
            Answer = max(Answer, dp[Deque.front()] * L);
        }
    }

    return Answer;
}

int main() {
    int T;
    for(scanf("%d", &T); T; T--) {
        readInput();
        makeLists();
        printf("%d\n", getAnswer());
    }

    return 0;
}
