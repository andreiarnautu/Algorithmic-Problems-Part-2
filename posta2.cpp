/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("posta2.in", "r", stdin);
FILE *fout = freopen("posta2.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*----------------------*/
int N, M;
int Tax[MAX_N];
bool Good[MAX_N];
vector< pair< int,int > > graph[MAX_N];
/*----------------------*/
int Root;
int degree[MAX_N];
long long totalEdgeCost;
/*----------------------*/

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i < N; i++) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        graph[u].push_back(make_pair(v, c));
        graph[v].push_back(make_pair(u, c));
    }
    for(int i = 1; i <= N; i++) {
        scanf("%d", &Tax[i]);
    }
    for(int i = 1; i <= M; i++) {
        int u; scanf("%d", &u);
        Good[u] = true;
        Root = u;
    }
}

void DFS(int node = Root, int father = 0) {
    for(vector< pair< int,int > >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(it->first != father) {
            DFS(it->first, node);
            Good[node] |= Good[it->first];
        }
    }

    if(!Good[node]) {return;}

    for(vector< pair< int,int > >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(it->first == father) {
            degree[node]++;
        } else {
            if(Good[it->first]) {
                degree[node]++; totalEdgeCost += 1LL * it->second;
            }
        }
    }
}

void writeOutput() {
    long long Answer = totalEdgeCost * 2;
    long long Best = 0;

    for(int i = 1; i <= N; i++) {
        if(Good[i]) {
            Answer += 1LL * Tax[i] * (degree[i] - 1);
            Best = max(Best, 1LL * Tax[i] * (degree[i] - 1));
        }
    }

    printf("%lld", Answer - Best);
}

int main() {
    readInput();
    DFS();
    writeOutput();
    return 0;
}
