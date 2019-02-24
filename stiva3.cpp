/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("stiva3.in", "r", stdin);
FILE *fout = freopen("stiva3.out", "w", stdout);

const int MAX_K = 1 + 50000;
const int MAX_INF = 2000000000 + 1;

int k;
deque <int> deq, A, B;
deque <int>::iterator it;
int maxElem;

bool found[MAX_K];

void readData() {
    for(int i = 1; i <= k; ++i) {
        int x; scanf("%d", &x);
        deq.push_back(x);
    }
}

int getMin() {
    int answer = MAX_INF;
    for(it = deq.begin(); it != deq.end(); ++it) {
        answer = min(answer, *it);
        maxElem = max(maxElem, *it);
    }
    return answer;
}

int decreaseValues(int val) {
    int answer = 0;
    for(int i = 0; i < (int)deq.size(); ++i) {
        deq[i] -= (val - 1);
        found[deq[i]] = true;
        if(deq[i] == 1) {
            answer = i;
        }
    }

    maxElem -= (val - 1);
    return answer;
}

int getMaxSt(int pos) {
    int answer = 0;
    for(int i = 0; i < pos; ++i) {
        answer = max(answer, deq[i]);
    }
    return answer;
}

void addSt(int val) {
    for(int i = val; i >= 1; i--) {
        if(!found[i]) {
            deq.push_front(i);
        }
    }
}

void addDr(int val) {
    for(int i = maxElem; i > val; --i) {
        if(!found[i]) {
            deq.push_back(i);
        }
    }
}

bool isSolveable() {
    for(int i = 1; i <= maxElem + 1; ++i) {
        A.push_back(i);
    }

    while(deq.size() != 0) {
        if(deq.front() >= A.front()) {
            for(int i = A.front(); i < deq.front(); ++i) {
                B.push_front(i);
                A.pop_front();
            }
            deq.pop_front(); A.pop_front();
        }
        else {
            if(B.front() == deq.front()) {
                deq.pop_front(); B.pop_front();
            }
            else {
                return false;
            }
        }
    }

    return true;
}

void solveSequence() {
    maxElem = 0;
    int minElem = getMin();
    int splitPos = decreaseValues(minElem);
    int maxSt = getMaxSt(splitPos);
    addSt(maxSt);
    addDr(maxSt);
    printf("%d\n", isSolveable());
}

void Reset() {
    for(int i = 1; i < MAX_K; ++i) {
        found[i] = false;
    }
    deq.clear(); A.clear(); B.clear();
}

int main() {
    scanf("%d", &k);
    for(int i = 1; i <= 5; ++i) {
        readData();
        solveSequence();
        Reset();
    }
}
