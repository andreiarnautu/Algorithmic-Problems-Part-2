/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("pm2.in", "r", stdin);
FILE *fout = freopen("pm2.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_INF = 0x3fffffff;

vector <int> ancestors[MAX_N];
vector <int> sons[MAX_N];
int Time[MAX_N];
int n;

bool isLeaf[MAX_N];
int minTime[MAX_N];
int bonusTime[MAX_N];

void readData() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &Time[i]);
        isLeaf[i] = true;
    }
    for(int i = 1; i <= n; ++i) {
        int cnt; scanf("%d", &cnt);
        for(int j = 1; j <= cnt; ++j) {
            int x; scanf("%d", &x);
            ancestors[i].push_back(x);
            sons[x].push_back(i);
            isLeaf[x] = false;
        }
    }
}

void initialize() {
    for(int i = 1; i <= n; ++i) {
        minTime[i] = -1;
        bonusTime[i] = -1;
    }
}

void computeTime(int node) {
    if(ancestors[node].size() == 0) {
        minTime[node] = Time[node];
    }
    else {
        minTime[node] = -1;
        for(vector <int>::iterator it = ancestors[node].begin(); it != ancestors[node].end(); ++it) {
            if(minTime[*it] == -1) {
                computeTime(*it);
            }
            minTime[node] = max(minTime[node], minTime[*it]);
        }
        minTime[node] += Time[node];
    }
}

int totalTime;

void getTotalTime() {
    for(int i = 1; i <= n; ++i) {
        if(minTime[i] == -1) {
            computeTime(i);
        }
    }

    totalTime = 0;
    for(int i = 1; i <= n; ++i) {
        totalTime = max(totalTime, minTime[i]);
    }
    printf("%d\n", totalTime);
}

void updateBonusTime(int node) {
    if(!sons[node].size()) {
        bonusTime[node] = 0;
    }
    else {
        bonusTime[node] = 0;
        for(vector <int>::iterator it = sons[node].begin(); it != sons[node].end(); ++it) {
            if(bonusTime[*it] == -1) {
                updateBonusTime(*it);
            }
            bonusTime[node] = max(bonusTime[node], bonusTime[*it] + Time[*it]);
        }
    }
}

void getMaxStartingTime() {
    for(int i = 1; i <= n; ++i) {
        if(bonusTime[i] == -1) {
            updateBonusTime(i);
        }
    }
}

void writeData() {
    for(int i = 1; i <= n; ++i) {
        int a = minTime[i] - Time[i];
        int b = totalTime - Time[i] - bonusTime[i];
        printf("%d %d\n", a, b);
    }
}

int main() {

    readData();
    initialize();
    getTotalTime();
    getMaxStartingTime();
    writeData();
    return 0;
}
