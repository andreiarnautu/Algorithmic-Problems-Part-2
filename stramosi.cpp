/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("stramosi.in", "r", stdin);
FILE *fout = freopen("stramosi.out", "w", stdout);

const int MAX_N = 1 + 250000,
          MAX_LOG = 20,
          bufferSize = 10000;

class inputReader {

private:
        char buffer[bufferSize];
        int pos;

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
};

inputReader cin;

bool solved[MAX_N];
int ancestor[MAX_N][MAX_LOG];
int lg[MAX_N];
int n, m;

void readData() {

    cin.getBuffer();
    cin.getInt(n); cin.getInt(m);

    for(int i = 1; i <= n; ++i)
        cin.getInt(ancestor[i][0]);
}

void computeAncestors(int node) {

    solved[node] = true;
    if(!solved[ancestor[node][0]])
        computeAncestors(ancestor[node][0]);
    for(int i = 1; ancestor[node][i - 1]; ++i)
        ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
}

void computeLogarithms() {

    for(int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
}

int getAncestor(int x, int q) {

    if(q == 0)
        return x;
    if(q >= n || x == 0)
        return 0;
    return getAncestor(ancestor[x][lg[q]], q - (1 << lg[q]));
}

int main() {

    readData();
    solved[0] = true;
    for(int i = 1; i <= n; ++i)
        if(!solved[i])
            computeAncestors(i);
    computeLogarithms();
    for(int i = 1; i <= m; ++i) {

        int p, q;
        cin.getInt(p); cin.getInt(q);
        printf("%d\n", getAncestor(p, q));
    }
    return 0;
}
