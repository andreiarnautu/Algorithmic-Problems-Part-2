/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("produse.in", "r", stdin);
FILE *fout = freopen("produse.out", "w", stdout);

const int MAX_N = 200000,
          bufferSize = 50000,
          MOD = 1000000000 + 7;

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

deque < int > nr;

int n, d;
int v[1 + MAX_N], cnt[1 + MAX_N];
bool inDeque[1 + MAX_N];

void readData() {

    cin.getBuffer();
    cin.getInt(n); cin.getInt(d);
    for(int i = 1; i <= n; ++i)
        cin.getInt(v[i]);
    sort(v + 1, v + n + 1);
}

int binarySearch(int val) {

    int left = 0, right = nr.size() - 1, mid, sol = 0;

    while(left <= right) {

        mid = (left + right) >> 1;
        if(nr[mid] <= val)
            sol = mid, left = mid + 1;
        else
            right = mid - 1;
    }
    return sol;
}

int main() {

    readData();
    cnt[1] = 1; nr.push_back(1); inDeque[1] = true;

    for(int i = 1; i <= n; ++i) {

        int limit = d / v[i];
        int pos = binarySearch(limit);
        for(int j = pos; j >= 0; --j)
            cnt[v[i] * nr[j]] = (cnt[v[i] * nr[j]] + cnt[nr[j]]) % MOD;
        for(int j = pos; j >= 0; --j)
            if(!inDeque[v[i] * nr[j]]) {

                int k = binarySearch(v[i] * nr[j]);
                nr.insert(nr.begin() + k + 1, v[i] * nr[j]);
                inDeque[v[i] * nr[j]] = true;
            }

    }
    cnt[1]--;
    if(cnt[1] == -1)
        cnt[1] = MOD - 1;

    int sol = 0;
    for(int i = 1; i <= d; ++i)
        sol = (sol + cnt[i]) % MOD;
    printf("%d", sol);
    return 0;
}
