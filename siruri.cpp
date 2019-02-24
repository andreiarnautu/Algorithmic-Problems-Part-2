/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("siruri.in", "r", stdin);
FILE *fout = freopen("siruri.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;
const long long BASE = 200003;
const long long P1 = 1000000007;
const long long P2 = 1000000009;

class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {

            return('0' <= c && c <= '9');
        }
public:

        void getBuffer() {

            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {

            char sign = '+';
            nr = 0;

            while(!digit(buffer[pos])) {
                sign = buffer[pos];
                if(++pos == bufferDim) {
                    getBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
            if(sign == '-') {
                nr = -nr;
            }
        }
} cin;

long long pow(long long base, long long exp, long long p) {
    long long answer = 1, aux = base;
    for(long long i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (answer * aux) % p;
        }
        aux = (aux * aux) % p;
    }

    return answer;
}

struct Hash {

public:
        long long r1, r2;
        int pos;
        bool where;

        Hash() {
            this->r1 = this->r2 = this->pos = this->where = 0;
        }

        void reset() {
            this->r1 = this->r2 = 0;
        }

        bool operator <(const Hash &other) const{
            if(this->r1 != other.r1) {
                return this->r1 < other.r1;
            }
            else {
                return this->r2 < other.r2;
            }
        }

        bool operator ==(const Hash &other) const{
            return (this->r1 == other.r1 &&
                    this->r2 == other.r2 &&
                    this->where != other.where);
        }

        void push_back(long long value) {
            this->r1 = (this->r1 * BASE + value + P1) % P1;
            this->r2 = (this->r2 * BASE + value + P2) % P2;
        }

        void pop_front(long long value, long long pow1, long long pow2) {
            this->r1 = (this->r1 - value * pow1 + BASE * P1) % P1;
            this->r2 = (this->r2 - value * pow2 + BASE * P2) % P2;
        }
};

int n, m;
int a[MAX_N], b[MAX_N];

void readData() {

    cin.getBuffer();
    cin.getInt(n);
    for(int i = 1; i <= n; ++i) {
        cin.getInt(a[i]);
    }
    cin.getInt(m);
    for(int i = 1; i <= m; ++i) {
        cin.getInt(b[i]);
    }
}

void initialize() {
    for(int i = 1; i < n; ++i) {
        a[i] = a[i] - a[i + 1];
    }
    for(int i = 1; i < m; ++i) {
        b[i] = b[i + 1] - b[i];
    }
}

vector <Hash> vec;

pair<int,int> rollingHash(int len) {

    vec.clear();
    Hash h;

    h.where = 0; h.pos = 1;
    for(int i = 1; i <= len; ++i) {
        h.push_back((long long)a[i]);
    }
    vec.push_back(h);

    long long pow1 = pow(BASE, len, P1);
    long long pow2 = pow(BASE, len, P2);

    for(int i = len + 1; i < n; ++i) {
        h.push_back((long long)a[i]);
        h.pop_front((long long)a[i - len], pow1, pow2);
        h.pos = i - len + 1;
        vec.push_back(h);
    }

    h.reset();
    h.where = 1; h.pos = 1;
    for(int i = 1; i <= len; ++i) {
        h.push_back((long long)b[i]);
    }
    vec.push_back(h);

    for(int i = len + 1; i < m; ++i) {
        h.push_back((long long)b[i]);
        h.pop_front((long long)b[i - len], pow1, pow2);
        h.pos = i - len + 1;
        vec.push_back(h);
    }

    sort(vec.begin(), vec.end());

    for(int i = 0; i < (int)vec.size(); ++i)
        if(vec[i] == vec[i + 1]) {
            if(vec[i].where == 0) {
                return make_pair(vec[i].pos, vec[i + 1].pos);
            }
            else {
                return make_pair(vec[i + 1].pos, vec[i].pos);
            }
        }
    return make_pair(0, 0);
}

void binarySearch() {
    int left = 2, right = min(m, n) - 1, answer = 1, posA = 1, posB = 1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        pair<int,int> p = rollingHash(mid);

        if(p.first != 0) {
            answer = mid + 1;
            posA = p.first;
            posB = p.second;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    printf("%d %d %d", answer, posA, posB);
}

int main() {

    readData();
    initialize();
    binarySearch();
    return 0;
}
