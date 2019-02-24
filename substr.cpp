/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("substr.in", "r", stdin);
FILE *fout = freopen("substr.out", "w", stdout);

const int MAX_N = 16500;
const int BASE = 157;
const int P1 = 30011;
const int P2 = 30013;

int pow(int base, int exp, int p) {
    int answer = 1, aux = base;
    for(int i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (answer * aux) % p;
        }
        aux = (aux * aux) % p;
    }

    return answer;
}

int val(char c) {
    return c;
}

class Hash {

public:
        int r1, r2;

        Hash() {
            this->r1 = this->r2 = 0;
        }

        bool operator ==(const Hash &other) const {
            return (this->r1 == other.r1 &&
                    this->r2 == other.r2);
        }

        bool operator <(const Hash &other) const {
            if(this->r1 != other.r1) {
                return this->r1 < other.r1;
            }
            else {
                return this->r2 < other.r2;
            }
        }

        void push_back(char c) {
            this->r1 = (this->r1 * BASE + val(c)) % P1;
            this->r2 = (this->r2 * BASE + val(c)) % P2;
        }
        void pop_front(char c, int pow1, int pow2) {
            this->r1 = (this->r1 - val(c) * pow1 + BASE * P1) % P1;
            this->r2 = (this->r2 - val(c) * pow2 + BASE * P2) % P2;
        }
};

int n, k;
char s[MAX_N];

void readData() {
    scanf("%d%d ",&n, &k);
    gets(s);
}

vector <Hash> vec;

bool rollingHash(int len) {

    Hash h;
    for(int i = 0; i < len; ++i) {
        h.push_back(s[i]);
    }

    vec.clear();
    vec.push_back(h);

    int pow1 = pow(BASE, len, P1);
    int pow2 = pow(BASE, len, P2);

    for(int i = len; i < n; ++i) {
        h.push_back(s[i]);
        h.pop_front(s[i - len], pow1, pow2);
        vec.push_back(h);
    }

    sort(vec.begin(), vec.end());
    int current = 1;
    if(k == 1) {
        return true;
    }

    for(int i = 1; i < (int)vec.size(); ++i) {
        if(vec[i] == vec[i - 1]) {
            ++current;
        }
        else {
            current = 1;
        }
        if(current == k) {
            return true;
        }
    }

    return false;
}

int binarySearch() {

    int left = 1, right = n, answer = 0;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(rollingHash(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return answer;
}

int main() {

    readData();
    printf("%d", binarySearch());
    return 0;
}
