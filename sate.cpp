/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back
#define MAX_N       1 + 30000
#define buffDIM     50000

using namespace std;
FILE *fin=freopen("sate.in","r",stdin);
FILE *fout=freopen("sate.out","w",stdout);

queue <int> Q;
vector < pair<int,int> > G[MAX_N];

char buffer[buffDIM];
bool ok[MAX_N];
bool found;
int dist[MAX_N];
int pos, n, m, x, y;

void read(int &nr) {

    while(buffer[pos] < '0' || '9' < buffer[pos])
        if(++pos == buffDIM)
            fread(buffer, 1, buffDIM, stdin), pos = 0;
    nr = 0;
    while('0' <= buffer[pos] && buffer[pos] <= '9') {

        nr = nr * 10 + buffer[pos] - '0';
        if(++pos == buffDIM)
            fread(buffer, 1, buffDIM, stdin), pos = 0;
    }
}

void readData() {

    fread(buffer, 1, buffDIM, stdin);
    read(n); read(m); read(x); read(y);
    int a, b, d;
    for(int i = 1; i <= m; ++i) {

        read(a); read(b); read(d);
        if(a > b)
            swap(a, b);
        G[a].pb(mp(b, d));
        G[b].pb(mp(a, -d));
    }
}

void dfs(int node) {

    for(vector < pair<int,int> >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!ok[it->fi]) {

            ok[it->fi] = 1;
            dist[it->fi] = dist[node] + it->se;
            if(it->fi == y) {

                found = 1;
                return;
            }
            dfs(it->fi);
            if(found)
                return;
        }
}

int main() {

    readData();
    ok[x] = 1;
    dfs(x);
    printf("%d", abs(dist[y]));
    return 0;
}

