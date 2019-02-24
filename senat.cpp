/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("senat.in", "r", stdin);
FILE *fout = freopen("senat.out", "w", stdout);

const int bufferDim = 1 + 100000;
const int MAX_N = 1 + 1000;

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
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }

        bool nextLine() {
            if(buffer[pos] == '\n') {
                pos++;
                return true;
            } else {
                return false;
            }
        }

        void checkBlank() {
            while(buffer[pos] != '\n' && !digit(buffer[pos])) {
                pos++;
            }
        }
} cin;

/*-----------------------*/
int N, M;
vector< int > G[MAX_N];
/*-----------------------*/
bool checked[MAX_N];
int left[MAX_N], right[MAX_N];

int cuplaj;
/*-----------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);

    int line = 1;
    while(line <= M) {
        int x; cin.getInt(x);
        G[line].push_back(x);

        cin.checkBlank();
        while(cin.nextLine()) {
            line++;
        }
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(vector< int >::iterator nxt = G[node].begin(); nxt != G[node].end(); nxt++) {
        if(!right[*nxt]) {
            left[node] = *nxt;
            right[*nxt] = node;

            cuplaj++;
            return true;
        }
    }

    for(vector< int >::iterator nxt = G[node].begin(); nxt != G[node].end(); nxt++) {
        if(pairUp(right[*nxt])) {
            left[node] = *nxt;
            right[*nxt] = node;

            return true;
        }
    }

    return false;
}

void hopcroftKarp() {
    bool ok;
    do {
        ok = false;
        for(int i = 1; i <= M; i++) {
            checked[i] = false;
        }
        for(int i = 1; i <= M; i++) {
            if(!left[i]) {
                ok |= pairUp(i);
            }
        }
    }while(ok);
}

void writeData() {
   // printf("%d\n", cuplaj);

    if(cuplaj < M) {
        printf("0\n");
    } else {
        for(int i = 1; i <= M; i++) {
            printf("%d\n", left[i]);
        }
    }
}

int main() {
    readData();
    hopcroftKarp();
    writeData();

    return 0;
}
