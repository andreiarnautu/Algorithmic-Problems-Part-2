/**
  *  Worg
  */
#include <cstdio>
#include <vector>
 
using namespace std;
FILE *fin = freopen("sortop.in", "r", stdin);
FILE *fout = freopen("sortop.out", "w", stdout);
 
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
/*--------------------*/
int N, K;
int pos[MAX_N];
vector<int> G[MAX_N];
/*--------------------*/
bool possible[MAX_N], folosit[MAX_N];
int subTree[MAX_N], numerotare[MAX_N], SOL[MAX_N];
int minim = 10000000, minNode;
/*--------------------*/
 
void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(K);
    for(int i = 1; i < N; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i = 1; i <= K; ++i) {
        int x, y; cin.getInt(x); cin.getInt(y);
        pos[x] = y;
        if(y < minim) {
            minNode = x; minim = y;
        }
    }
}
 
void checkPossibilities(int node, int dist = 0) {
    possible[node] = true;
    for(vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(!possible[*it] && !pos[*it] && dist + 1 < pos[minNode]) {
            checkPossibilities(*it, dist + 1);
        }
    }
}
 
bool ok;
 
void DFS(int node, int maxVal = 0) {
    if(pos[node] && maxVal > pos[node]) {
        ok = false;
    }
    if(!ok) {
        return;
    }
 
    if(pos[node]) {
        numerotare[node] = pos[node];
    } else {
        for(int i = maxVal + 1; i <= N; ++i) {
            if(!folosit[i]) {
                folosit[i] = true;
                numerotare[node] = i;
                break;
            }
        }
    }
    for(vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(!numerotare[*it]) {
            DFS(*it, numerotare[node]);
        }
    }
}
 
void Try(int root) {
    for(int i = 1; i <= N; ++i) {
        folosit[i] = false;
    }
    for(int i = 1; i <= N; ++i) {
        subTree[i] = 0; numerotare[i] = 0;
        if(pos[i]) {
            folosit[pos[i]] = true;
        }
    }
    ok = true;
    DFS(root);
    if(ok) {
        for(int i = 1; i <= N; ++i) {
            SOL[numerotare[i]] = i;
        }
        for(int i = 1; i <= N; ++i) {
            printf("%d ", SOL[i]);
        }
    }
}
 
int main() {
    readData();
    checkPossibilities(minNode);
    for(int i = 1; i <= N; ++i) {
        if(possible[i] && !pos[i]) {
            Try(i);
            if(ok) {
                return 0;
            }
        }
    }
    printf("-1");
    return 0;
}
