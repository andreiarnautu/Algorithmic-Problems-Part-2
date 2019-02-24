/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("reinvent.in", "r", stdin);
FILE *fout = freopen("reinvent.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 100000;

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

/*-----------------*/
int N, M, X;
vector< int > graph[MAX_N];
/*-----------------*/
queue< int > Q;
int nodeColor[MAX_N];
int minDist[MAX_N];

int Solution = MAX_N;
/*-----------------*/

void readInput() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M); cin.getInt(X);
    for(int i = 1; i <= M; i++) {
        int u, v; cin.getInt(u); cin.getInt(v);
        graph[v].push_back(u); graph[u].push_back(v);
    }
    for(int i = 1; i <= X; i++) {
        int u; cin.getInt(u);
        Q.push(u);
        nodeColor[u] = i;
    }
}

void Expand(int node) {
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(nodeColor[*it]) { /* if the neighbour has already been reached */
            if(nodeColor[*it] != nodeColor[node]) {
                Solution = min(Solution, minDist[*it] + minDist[node] + 1);
            }
        } else {
            nodeColor[*it] = nodeColor[node];
            minDist[*it] = minDist[node] + 1;
            Q.push(*it);
        }
    }
}

void solveProblem() {
    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        Expand(node);
    }
}

void writeOutput() {
    printf("%d\n", Solution);
}

int main() {
    readInput();
    solveProblem();
    writeOutput();

    return 0;
}
