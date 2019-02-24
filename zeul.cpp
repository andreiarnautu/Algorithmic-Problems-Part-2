/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("zeul.in", "r", stdin);
FILE *fout = freopen("zeul.out", "w", stdout);

const int MAX_N = 1 + 100000;

vector < pair<int,int> > sol;

int degree[MAX_N];
int n, m;

void readData() {

    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= m; ++i) {

        int x, y; scanf("%d %d ", &x, &y);
        ++degree[x], --degree[y];
    }
}

void solveProblem() {

    int p1, p2;
    for(p1 = 1; degree[p1] >= 0 && p1 <= n + 1; p1++);
    for(p2 = 1; degree[p2] <= 0 && p2 <= n + 1; p2++);

    while(p1 <= n && p2 <= n) {

        sol.pb(make_pair(p1, p2));
        ++degree[p1], --degree[p2];
        for(; degree[p1] >= 0 && p1 <= n + 1; ++p1);
        for(; degree[p2] <= 0 && p2 <= n + 1; ++p2);
    }

    printf("%d\n", sol.size());
    for(vector < pair<int,int> >::iterator it = sol.begin(); it != sol.end(); ++it)
        printf("%d %d\n", it->first, it->second);
}

int main() {

    readData();
    solveProblem();
    return 0;
}
