/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("progr.in", "r", stdin);
FILE *fout = freopen("progr.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int mask = (1 << 14) - 1;

int n;
int vec[MAX_N];
vector <int> h[mask + 1];

void setData() {

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &vec[i]);
        h[vec[i] & mask].push_back(vec[i]);
    }

    sort(vec + 1, vec + n + 1);
}

bool find(int key) {
    int level = key & mask;
    for(vector <int>::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(*it == key) {
            return true;
        }
    return false;
}

int getAnswer() {
    int answer = 0;
    for(int i = 1; i < n; ++i)
        for(int j = i + 1; j <= n; ++j) {
            int diff = vec[j] - vec[i];
            if(vec[i] - diff <= 0 || !find(vec[i] - diff)) {
                answer++;
            }
        }
    return answer;
}

void cleanUp() {
    for(int i = 1; i <= n; ++i)
        h[vec[i] & mask].clear();
}

int main() {
    int testCount;
    for(scanf("%d", &testCount); testCount; --testCount) {
        setData();
        printf("%d\n", getAnswer());
        cleanUp();
    }
    return 0;
}
