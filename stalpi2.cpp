/**
  *  Worg
  */
#include <cmath>
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("stalpi2.in", "r", stdin);
FILE *fout = freopen("stalpi2.out", "w", stdout);

const int MAX_N = 1 + 50;
const int MAX_D = 1 + 10000;
const int MAX_INF = 1000000;

/*--------------------*/
int N, E;
int dist[MAX_N];
/*--------------------*/
int dp[MAX_N][MAX_D], best[MAX_N][MAX_D];
deque< int > Deque;
/*--------------------*/

void readInput() {
    scanf("%d%d", &N, &E);
    for(int i = 2; i <= N; i++) {
        scanf("%d", &dist[i]);
    }
}

int getEffort(const int D) {
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j <= dist[N]; j++) {
            best[i][j] = dp[i][j] = MAX_INF;
        }
    }

    dp[1][0] = best[1][0] = 0;
    for(int i = 1; i <= dist[N]; i++) {
        dp[1][i] = MAX_INF;
        if(i > D) {
            best[1][i] = MAX_INF;
        } else {
            best[1][i] = 0;
        }
    }

    for(int i = 2; i <= N - 1; i++) {
        for(int j = 0; j <= dist[N]; j++) {
            dp[i][j] = best[i - 1][j] + abs(j - dist[i]);

            if(!Deque.empty() && Deque.front() == j - D - 1) {
                Deque.pop_front();
            }
            while(!Deque.empty() && dp[i][j] <= dp[i][Deque.back()]) {
                Deque.pop_back();
            }
            Deque.push_back(j);

            best[i][j] = dp[i][Deque.front()];
        }
        Deque.clear();
    }

    return best[N - 1][dist[N]];
}

int getMinDist() {
    int left = 0, right = dist[N], Answer = 0;

    while(left <= right) {
        int mid = (left + right) >> 1;
        int Effort = getEffort(mid);

        if(Effort <= E) {
            Answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return Answer;
}

int main() {
    readInput();
    printf("%d", getMinDist());
    return 0;
}
