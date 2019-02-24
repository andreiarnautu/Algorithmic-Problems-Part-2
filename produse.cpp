/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("produse.in", "r", stdin);
FILE *fout = freopen("produse.out", "w", stdout);

const int MAX_N = 200000, MOD = 1000000000 + 7, bufferSize = 10000;

class inputReader {

private:
    int pos;
    char buffer[bufferSize];

public:

    void getBuffer() {

        fread(buffer, 1, bufferSize, stdin);
        pos = 0;
    }

    bool digit(char c) {

        return ('0' <= c && c <= '9');
    }

    void getInt(int &nr) {

        nr = 0;
        while(!digit(buffer[pos]))
            if(++pos == bufferSize)
                getBuffer();
        while(digit(buffer[pos])) {

            nr = nr * 10 + buffer[pos] - '0';
            if(++pos == bufferSize)
                getBuffer();
        }
    }
} cin;

int appCount[1 + MAX_N], cnt[1 + MAX_N], notAdded[1 + MAX_N];
int n, d;

int fact[1 + MAX_N], invMod[1 + MAX_N];
int phi;

void readData() {

    cin.getBuffer();
    cin.getInt(n); cin.getInt(d);
    for(int i = 1; i <= n; ++i) {

        int x; cin.getInt(x);
        appCount[x]++;
    }
}

int getInvMod(int value) {

    int ret = 1, aux = value, power = phi - 1;
    for(int i = 1; i <= power; i <<= 1) {

        if(i & power)
            ret = (1LL * ret * aux) % MOD;
        aux = (1LL * aux * aux) % MOD;
    }
    return ret;
}

void getNumericValues() {

    /* 10^9 + 7 is prime */
    phi = MOD - 1;

    fact[0] = invMod[0] = 1;
    for(int i = 1; i <= MAX_N; ++i) {

        fact[i] = (1LL * fact[i - 1] * i) % MOD;
        invMod[i] = getInvMod(fact[i]);
    }
}

int getComb(int N, int K) {

    if(K == 1)
        return N;
    if(N == K)
        return 1;

    int ret = fact[N];
    ret = (1LL * ret * invMod[K]) % MOD;
    ret = (1LL * ret * invMod[N - K]) % MOD;
    return ret;
}

void updateCnt(int value) {

    int limit = (d / value) * value;
    for(int i = limit; i >= value; i -= value) {

        int j = i, exponent = 1;
        while(j % value == 0 && exponent <= appCount[value]) {

            cnt[i] = (1LL * cnt[i] + 1LL * getComb(appCount[value], exponent) * cnt[j / value]) % MOD;
            j /= value; exponent++;
        }
    }
}

int main() {

    readData();
    getNumericValues();

    cnt[1] = 1;
    int aux = 2, power = appCount[1];
    for(int i = 1; i <= power; i <<= 1) {

        if(i & power)
            cnt[1] = (1LL * cnt[1] * aux) % MOD;
        aux = (1LL * aux * aux) % MOD;
    }

    for(int i = 2; i <= d; ++i)
        if(appCount[i])
            updateCnt(i);


    --cnt[1];
    if(cnt[1] == -1)
        cnt[1] = MOD - 1;
    int sol = 0;
    for(int i = 1; i <= d; i++)
        sol = (sol + cnt[i]) % MOD;
    printf("%d", sol);
    return 0;
}
