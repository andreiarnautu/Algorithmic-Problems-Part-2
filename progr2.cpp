/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("progr2.in", "r", stdin);
FILE *fout = freopen("progr2.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int mask = (1 << 16) - 1;

int n;
int vec[MAX_N];

int dp[MAX_N][MAX_N];
vector <int> h[mask + 1];

void readData() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &vec[i]);
    }
}

int find(int key) {
    int level = key & mask;
    for(vector <int>::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(vec[*it] == key) {
            return *it;
        }
    return 0;
}

int getAnswer() {
    int answer = 0;
    h[vec[1] & mask].push_back(1);

    for(int i = 2; i <= n; ++i) {

        for(int j = 1; j < i; ++j) {
            int diff = vec[i] - vec[j], current = 0;

            if(vec[j] - diff > 0) {
                int index = find(vec[j] - diff);
                if(index != 0 && index < j) {
                    current = dp[j][index];
                }
            }
            dp[i][j] = current + 1;
            answer += dp[i][j];

        }
        h[vec[i] & mask].push_back(i);
    }

    return answer;
}

void cleanUp() {
    for(int i = 1; i <= n; ++i)
        h[vec[i] & mask].clear();
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j < i; ++j)
            dp[i][j] = 0;
}

int main() {

    int testCount;
    //printf("%.3f\n", (float)sizeof(h) / 1024);
    for(scanf("%d", &testCount); testCount; testCount--) {
        readData();
        printf("%d\n", getAnswer());
        cleanUp();
    }
}
