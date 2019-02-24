/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("vecini2.in", "r", stdin);
FILE *fout = freopen("vecini2.out", "w", stdout);

const int sigma = 27;
const int MAX_N = 1 + 5000;

char A[MAX_N], B[MAX_N];
int n;

int cntA[sigma], cntB[sigma], cnt[sigma];

char sol[MAX_N];

void readData() {
    scanf("%d", &n);
    scanf("%s%s", A, B);
}

int val(char c) {
    return c - 'a';
}

void preProcess() {
    for(int i = 0; i < n; ++i) {
        cntA[val(A[i])]++;
    }
    for(int i = 0; i < n; ++i) {
        cntB[val(B[i])]++;
    }
}

bool solved, how;

int lowerThan(int value) {
    for(int i = value - 1; i >= val('a'); --i) {
        if(cnt[i]) {
            return i;
        }
    }
    return -1;
}

int greaterThan(int value) {
    for(int i = value + 1; i <= val('z'); ++i) {
        if(cnt[i]) {
            return i;
        }
    }
    return -1;
}

void first(int pos) {

    if(pos == n) {
        if(how == 1) {
            solved = true;
        }
        return;
    }

    if(how == 0) {
        if(cnt[val(A[pos])]) {
            cnt[val(A[pos])]--;
            sol[pos] = A[pos];
            first(pos + 1);

            if(!solved) {
                cnt[val(A[pos])]++;
                int x = lowerThan(val(A[pos]));
                if(x == -1) {
                    return;
                }
                else {
                    sol[pos] = x + 'a';
                    cnt[x]--;
                    how = 1;
                    first(pos + 1);
                }
            }
        }
        else {
            int x = lowerThan(val(A[pos]));
            if(x == -1) {
                return;
            }
            else {
                sol[pos] = x + 'a';
                cnt[x]--;
                how = 1;
                first(pos + 1);
            }
        }
    }

    else {
        for(char c = 'z'; c >= 'a'; c--) {
            if(cnt[val(c)]) {
                sol[pos] = c;
                cnt[val(c)]--;
                first(pos + 1);
            }
        }
    }
}

void second(int pos) {
    if(pos == n) {
        if(how == 1) {
            solved = true;
        }
        return;
    }

    if(how == 0) {
        if(cnt[val(A[pos])]) {
            cnt[val(A[pos])]--;
            sol[pos] = A[pos];
            second(pos + 1);

            if(!solved) {
                cnt[val(A[pos])]++;
                int x = greaterThan(val(A[pos]));
                if(x == -1) {
                    return;
                }
                else {
                    sol[pos] = x + 'a';
                    cnt[x]--;
                    how = 1;
                    second(pos + 1);
                }
            }
        }
        else {
            int x = greaterThan(val(A[pos]));
            if(x == -1) {
                return;
            }
            else {
                sol[pos] = x + 'a';
                cnt[x]--;
                how = 1;
                second(pos + 1);
            }
        }
    }

    else {
        for(char c = 'a'; c <= 'z'; c++) {
            if(cnt[val(c)]) {
                sol[pos] = c;
                cnt[val(c)]--;
                second(pos + 1);
            }
        }
    }
}

void makeFirst() {
    for(int i = val('a'); i <= val('z'); ++i) {
        cnt[i] = cntB[i];
    }
    solved = how = false;
    first(0);

    if(!solved) {
        printf("0\n");
    }
    else {
        for(int i = 0; i < n; ++i) {
            printf("%c", sol[i]);
        }
        printf("\n");
    }
}

void makeSecond() {
    for(int i = val('a'); i <= val('z'); ++i) {
        cnt[i] = cntB[i];
    }
    solved = how = false;
    second(0);

    if(!solved) {
        printf("0\n");
    }
    else {
        for(int i = 0; i < n; ++i) {
            printf("%c", sol[i]);
        }
        printf("\n");
    }
}

int main() {
    readData();
    preProcess();
    makeFirst();
    makeSecond();
    return 0;
}
