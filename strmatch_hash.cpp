/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("strmatch.in", "r", stdin);
FILE *fout = freopen("strmatch.out", "w", stdout);

const int MAX_LEN = 1 + 2000000;
const int P1 = 30011;
const int P2 = 30013;

int BASE = 67;

int pow(int base, int exp, int P) {

    int answer = 1, aux = base;
    for(int i = 1; i <= exp; i *= 2) {
        if(i & exp) {
            answer = (answer * aux) % P;
        }
        aux = (aux * aux) % P;
    }

    return answer;
}

int val(char c) {

    if('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    if('a' <= c && c <= 'z') {
        return 26 + c - 'a';
    }
    return 52 + c - '0';
}

struct Hash {
    int r1, r2;
    int len;

    Hash() {
        this->r1 = this->r2 = this->len = 0;
    }

    bool operator ==(const Hash &other) const {
        return (this->r1 == other.r1 &&
                this->r2 == other.r2 &&
                this->len == other.len);
    }
};

Hash push_back(Hash h, char c) {
    Hash answer;
    answer.r1 = (h.r1 * BASE + val(c)) % P1;
    answer.r2 = (h.r2 * BASE + val(c)) % P2;
    answer.len = h.len + 1;

    return answer;
}

int precalc1, precalc2;

Hash pop_front(Hash h, char c) {
    Hash answer;
    answer.r1 = (h.r1 - val(c) * precalc1 + BASE * P1) % P1;
    answer.r2 = (h.r2 - val(c) * precalc2 + BASE * P2) % P2;
    answer.len = h.len - 1;

    return answer;
}

Hash getHash(char *s) {
    Hash answer;
    while(*s != '\0') {
        answer = push_back(answer, *s);
        s++;
    }

    return answer;
}

char P[MAX_LEN], T[MAX_LEN];
vector <int> sol;

int main() {

    gets(P); gets(T);
    int len1 = strlen(P), len2 = strlen(T);

    Hash h1 = getHash(P), h2;
    for(int i = 0; i < min(len2, len1); i++) {
        h2 = push_back(h2, T[i]);
    }

    precalc1 = pow(BASE, len1, P1);
    precalc2 = pow(BASE, len1, P2);

    if(h1 == h2) {
        sol.push_back(0);
    }

    for(int i = len1; i < len2; i++) {
        h2 = push_back(h2, T[i]);
        h2 = pop_front(h2, T[i - len1]);

        if(h1 == h2) {
            sol.push_back(i - len1 + 1);
        }
    }

    printf("%d\n", (int)sol.size());
    for(int i = 0; i < (int)sol.size() && i < 1000; i++) {
        printf("%d ", sol[i]);
    }
}
