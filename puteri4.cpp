/**
  *  Worg
  */
#include <bitset>
#include <cstdio>

using namespace std;
FILE *fin = freopen("puteri4.in", "r", stdin);
FILE *fout = freopen("puteri4.out", "w", stdout);

const int MAX_EXP = 1 + 60;

bool isPrime[MAX_EXP];

void primeNumbers() {
    for(int i = 2; i < MAX_EXP; ++i) {
        isPrime[i] = true;
    }
    for(int i = 2; i < MAX_EXP; i++) {
        if(isPrime[i]) {
            for(int j = i * 2; j < MAX_EXP; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

bool smaller(long long nr, long long exp, long long limit) {
    long long current = 1;
    for(int i = 1; i <= exp; ++i) {
        if(limit / current < nr) {
            return false;
        }
        current *= nr;
    }
    return true;
}

long long root(long long nr, int e) {
    long long left = 1, right = nr, answer = 1;
    while(left <= right) {
        long long mid = (left + right) >> 1;
        if(smaller(mid, e, nr)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return answer;
}

long long cnt(long long nr, int expMax) {
    if(nr == 0) {
        return 0;
    }


    long long answer = 1;
    for(int exp = 2; exp < expMax; exp++) {
        if(isPrime[exp]) {
            long long Root = root(nr, exp);
            if(Root > 1) {
                answer += Root;
                answer -= cnt(Root, exp);
            }
        }
    }

    return answer;
}

int main() {
    primeNumbers();
    int T;
    for(scanf("%d", &T); T; T--) {
        long long X, Y; scanf("%lld%lld", &X, &Y);
        printf("%lld\n", cnt(Y, MAX_EXP) - cnt(X - 1, MAX_EXP));
    }
    return 0;
}
