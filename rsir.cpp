/**
  *  Worg
  */
#include <cstdio>
#include <cstdlib>
#include <utility>

using std::pair;

FILE *fin = freopen("rsir.in", "r", stdin);
FILE *fout = freopen("rsir.out", "w", stdout);

const int kMaxM = 7000;

/*-------- Structures --------*/
struct Element {
    int value;
    int prev_A, prev_B;

    Element() {value = prev_A = prev_B = -1;}
    Element(const int value, const int prev_A, const int prev_B) {this->value = value; this->prev_A = prev_A; this->prev_B = prev_B;}

    bool operator ==(const Element &other) const {
        return (this->value == other.value && this->prev_A == this->prev_B);
    }

    bool operator !=(const Element &other) const {
        return (this->value != other.value || this->prev_A != other.prev_A);
    }
};
/*-------- Input data --------*/
int T0, T1, a, b, x, y, z, M;
long long n;

int precalc_A[kMaxM], precalc_B[kMaxM];
/*-------- Cycle Detection --------*/
Element x0;
/*-------- --------*/

void Precalc() {
    for(int i = 0; i < kMaxM; i++) {
        precalc_B[i] = 1LL * (1LL * a * i * i + 1LL * x * i) % M;
        precalc_A[i] = 1LL * (1LL * b * i * i + 1LL * y * i + 1LL * z) % M;
    }
}

Element GetNext(Element E0, Element E1) {
    Element E;
    E.prev_A = E1.value;
    E.prev_B = E0.value;

    E.value = precalc_A[E.prev_A] + precalc_B[E.prev_B];
    if(E.value >= M) {
        E.value -= M;
    }

    return E;
}

Element GetNext(Element E0) {
    Element E;
    E.prev_B = E0.prev_A;
    E.prev_A = E0.value;

    E.value = precalc_A[E.prev_A] + precalc_B[E.prev_B];
    E.value -= M * (E.value >= M);

    return E;
}

void ReadInput() {
    scanf("%d%d%d%d%d%d%d%d%lld", &T0, &T1, &a, &b, &x, &y, &z, &M, &n);
    T0 %= M;
    T1 %= M;
    a %= M;
    b %= M;
    x %= M;
    y %= M;
    z %= M;
}

pair<int, int > GetCycleParams() {   ///  Lambda = lungimea ciclului; Mu = lungimea cozii
    Element tortoise, hare;

    tortoise = GetNext(x0);
    hare = GetNext(GetNext(x0));

    while(tortoise != hare) {
        tortoise = GetNext(tortoise);
        hare = GetNext(GetNext(hare));
    }

    int mu = 0;
    tortoise = x0;
    while(tortoise != hare) {
        mu ++;
        tortoise = GetNext(tortoise);
        hare = GetNext(hare);
    }

    int lambda = 1;
    hare = GetNext(tortoise);
    while(tortoise != hare) {
        hare = GetNext(hare);
        lambda ++;
    }

    return std::make_pair(lambda, mu);
}

void WriteOutput(pair<int, int > params) {
    if(n == 0) {
        printf("%d\n", T0 % M);
    } else if(n == 1) {
        printf("%d\n", T1 % M);
    } else {
        int lambda = params.first, mu = params.second;

        n -= 2;
        if(n < mu) {
            Element now = x0;
            for(int i = 0; i < n; i++) {
                now = GetNext(now);
            }
            printf("%d\n", now.value);
        } else {
            Element now = x0;
            for(int i = 0; i < mu; i++) {
                now = GetNext(now);
            }
            n -= mu;
            n %= lambda;

            for(int i = 0; i < n; i++) {
                now = GetNext(now);
            }
            printf("%d\n", now.value);
        }
    }
}

int main() {
    ReadInput();
    Precalc();
    x0 = GetNext(Element(T0, -1, -1), Element(T1, -1, -1));
    pair<int, int > params = GetCycleParams();
    WriteOutput(params);
    return 0;
}
