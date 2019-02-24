/**
  *  Worg
  */
#include <set>
#include <queue>
#include <cstdio>
#include <algorithm>


using namespace std;
FILE *fin = freopen("produse.in", "r", stdin);
FILE *fout = freopen("produse.out", "w", stdout);

const int MAX_N = 400000,
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

queue < int > deAdaugat;
set < int > lista;

int freq[1 + MAX_N], add[1 + MAX_N], v[1 + MAX_N];
int n, d;

int main() {

    cin.getBuffer();
    cin.getInt(n);
    cin.getInt(d);
    freq[1] = 1;
    lista.insert(1);

    for(int i = 1; i <= n; ++i)
        cin.getInt(v[i]);

    sort(v + 1, v + n + 1);
    v[n + 1] = 200000;
    for(int i = 1; i <= n; ++i) {

        int maxNr = d / v[i], nextMaxNr = d / v[i + 1];
        set < int >::iterator it = lista.upper_bound(maxNr);
        if(it != lista.end()) {

            set < int >::iterator it1 = it; ++it1;
            lista.erase(it1, lista.end());
        }

        for(set < int >::iterator it2 = lista.begin(); it2 != it; it2++) {

            int k = *it2 * v[i];
            if(maxNr >= k) {

                deAdaugat.push(k);
                add[k] = freq[*it2];
            }
            else
                freq[k] = (freq[k] + freq[*it2]) % MOD;

        }
        while(!deAdaugat.empty()) {

            int val = deAdaugat.front(); deAdaugat.pop();
            if(nextMaxNr >= val)
                lista.insert(val);
            freq[val] = (add[val] + freq[val]) % MOD;
            add[val] = 0;
        }
    }

    int sol = 0;

    --freq[1];
    if(freq[1] == -1)
        freq[1] = MOD - 1;
    for(int i = 1; i <= d; i++)
        sol = (sol + freq[i]) % MOD;
    printf("%d\n", sol);
    return 0;
}
