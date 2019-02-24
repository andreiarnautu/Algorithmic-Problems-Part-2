/**
  *  Worg
  */
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
FILE *fin = freopen("sec.in", "r", stdin);
FILE *fout = freopen("sec.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 200000;

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
} cin;

/*-----------------------------*/
int N;
vector< int > G[MAX_N], below[MAX_N];

string id[MAX_N];
bool queryAnswer[MAX_N];
/*-----------------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v); G[v].push_back(u);
    }
}

bool Compare(int u, int v) {
    if(id[u].size() != id[v].size()) {
        return false;
    } else {
        for(int i = 0; i < (int)id[u].size(); i++) {
            if(id[u][i] != id[v][i]) {
                return false;
            }
        }
        return true;
    }
}

void DFS(int node = 1, int father = 0) {
    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(father != *it) {
            below[node].push_back(*it);
            DFS(*it, node);
        }
    }

    if(below[node].size() == 0) { /* if the node is a leaf */
        id[node] += '1';
        queryAnswer[node] = true;
    } else if(below[node].size() == 1) { /* if the node has only one son */
        id[node] = id[below[node][0]] + '1';
        id[below[node][0]].clear();
        queryAnswer[node] = false;
    } else { /* if the node has two sons */
        id[node] = id[below[node][0]] + '0' + id[below[node][1]];
        if(Compare(below[node][0], below[node][1])) {
            queryAnswer[node] = true;
        } else {
            queryAnswer[node] = false;
        }
        id[below[node][0]].clear(); id[below[node][1]].clear();

    }
}

void answerQueries() {
    int Q;
    for(cin.getInt(Q); Q; Q--) {
        int node; cin.getInt(node);
        if(queryAnswer[node] == true) {
            printf("DA\n");
        } else {
            printf("NU\n");
        }
    }
}

int main() {
    readData();
    DFS();
    answerQueries();
    return 0;
}
