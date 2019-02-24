/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>

#define fi      first
#define se      second
#define mp      make_pair
#define pb      push_back
#define dim     100100
#define inFile  "riremito.in"
#define outFile "riremito.out"
#define buffDim 10100

using namespace std;

FILE *fin=freopen(inFile, "r", stdin);
FILE *fout=freopen(outFile, "w", stdout);

vector < pair<int, int> > G[dim];
vector < pair<int, int> >::iterator it;
vector < int > v;
vector < int >::iterator it1;

long long int d[dim], father_son[dim], dleaf[dim]; // dleaf[i] = distanta minima de la nod pana la o frunza
long long int cost;
int sons[dim], father[dim], visited[dim];
int n, k, pos, start;
bool viz[dim], leaf[dim];
char buff[buffDim];

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDim)
            pos = 0, fread(buff, 1, buffDim, stdin);

    nr = 0;
    while(buff[pos] >= '0' && buff[pos]<= '9') {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim)
            pos = 0, fread(buff, 1, buffDim, stdin);
    }
}

bool comp(pair<int, int> a, pair<int, int> b) {

    return a.fi < b.fi;
}

void readData() {

    fread(buff, 1, buffDim, stdin);
    read(n);
    int x, y, z;

    for(int i = 1; i < n; ++i) {

        read(x); read(y); read(z);
        G[x].pb(mp(z, y));
        G[y].pb(mp(z, x));
    }

    for(int i = 1; i <= n; ++i) {

        sort(G[i].begin(), G[i].end(), comp);
    }

    read(k);
    for(int i = 1; i <= k; ++i) {

        read(x); v.pb(x);
    }
}

void getDist(int node) {        // get the distance from the root to every node. O(N)

    viz[node] = 1;
    sons[node] = 1;
    leaf[node] = 1;
    for(vector < pair<int, int> >::iterator it2 = G[node].begin(); it2 != G[node].end(); ++it2)
        if(!viz[it2->se]) {

            leaf[node] = 0;
            viz[it2->se] = 1;
            d[it2->se] = d[node] + 1LL * it2->fi;

            getDist(it2->se);

            sons[node] += sons[it2->se];
            father[it2->se] = node;
            father_son[it2->se] = 1LL * it2->fi;
            dleaf[node] = max(dleaf[node], dleaf[it2->se] + 1LL * it2->fi);
        }
    if(leaf[node])
        dleaf[node] = 0;
}

void visit(int node) {

    if(!viz[node])
        ++visited[node];
    viz[node] = 1;

    printf("%d %lld\n", node, cost);

    for(vector < pair<int, int> >::iterator it2 = G[node].begin(); it2 != G[node].end(); ++it2)
        if(sons[it2->se] && it2->se != father[node]) {

            cost += 1LL * it2->fi;
            visit(it2->se);

            if(!leaf[node])
                return;
            break;
        }

    if(!leaf[node])
        return;

    sons[node] = 0;

    int vertex = node;
    long long int dist = 0;

    while(vertex != start) {

        visited[father[vertex]] += visited[vertex];
        visited[father[father[vertex]]] += visited[father[vertex]];
        sons[father[vertex]] -= visited[father[vertex]];
        visited[father[vertex]] = 0;
        dist += father_son[vertex];

        if(!sons[vertex] && sons[father[vertex]])
            break;
        vertex = father[vertex];
    }

    if(vertex == start)
        return;
    cost += 1LL * min(d[father[vertex]], dist);
    visit(father[vertex]);
}

void init() {

       // for(int i = 1; i <= n + 1; ++i)
      //      viz[i] = sons[i] = visited[i] = father[i] = father_son[i] = leaf[i] = d[i] = dleaf[i] = 0;
        memset(viz, 0, sizeof(viz));
        memset(sons, 0, sizeof(sons));
        memset(visited, 0, sizeof(visited));
        memset(father, 0, sizeof(father));
        memset(father_son, 0, sizeof(father_son));
        memset(leaf, 0, sizeof(leaf));
        memset(d, 0, sizeof(d));
        memset(dleaf, 0, sizeof(dleaf));
}

int main() {

    readData();
    for(it1 = v.begin(); it1 != v.end(); ++it1) {

        start = *it1;
        init();
        getDist(start);

        for(int i = 1; i <= n; ++i) {

            for(int j = 1; j < G[i].size(); ++j) {

                int J = j;
                while(J > 0 && G[i][J].fi == G[i][J - 1].fi && (dleaf[G[i][J].se] < dleaf[G[i][J - 1].se] || father[i] == G[i][J - 1].se)) {

                    swap(G[i][J], G[i][J - 1]);
                    --J;
                }
            }
        }

        memset(viz, 0, sizeof(viz));
        cost = 0;
        visit(start);
        printf("%lld\n", cost);
    }
    return 0;
}
