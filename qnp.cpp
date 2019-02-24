/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("qnp.in", "r", stdin);
FILE *fout = freopen("qnp.out", "w", stdout);

const int mod = 1e9 + 7;
const int kMaxCif = 700001;

int test_count;
long long k;
int a[10];

long long fact[kMaxCif], inv_mod[kMaxCif];
int ans[kMaxCif];

int digits;

long long Power(long long base, long long exp) {
    long long answer = 1, aux = base;
    for(long long i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = answer * aux % mod;
        }
        aux = aux * aux % mod;
    }
    return answer;
}

void Precalc() {
    fact[0] = 1;

    for(int i = 1; i < kMaxCif; i++) {
        fact[i] = fact[i - 1] * i % mod;
        inv_mod[i] = Power(fact[i], mod - 2);
    }
}

void GetAns(int digit, long long K, int left) {
    long long under = 0;
    for(int i = 0; i <= 9; i++) {
        if(a[i]) {
            a[i] --;
            long long crt = fact[left - 1];
            for(int j = 0; j <= 9; j++) {
                if(!a[j]) continue;
                crt = crt * inv_mod(a[j]) % mod;
            }

        }
    }
}

int main() {
    Precalc();
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        digits = 0;
        for(int i = 0; i <= 9; i++) {
            scanf("%d", &a[i]);
            digits += a[i];
        }
        scanf("%lld", k);
        GetAns(1, k, digits);
    }
}
