/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("revolutie.in", "r", stdin);
FILE *fout = freopen("revolutie.out", "w", stdout);

const int MAX_N = 130;

/*-------------------------*/
int N;
vector< int > graph[MAX_N];
/*-------------------------*/ /** Cuplaj */
bool checked[MAX_N];
int left[MAX_N], right[MAX_N];
int Cuplaj;
/*-------------------------*/
vector< pair< int,int > > Sol;

void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            int x; scanf("%d", &x);
            if(x) {
                graph[i].push_back(j);
            }
        }
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!right[*it]) {
            left[node] = *it;
            right[*it] = node;
            Cuplaj++;

            return true;
        }
    }

    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(pairUp(right[*it])) {
            left[node] = *it;
            right[*it] = node;

            return true;
        }
    }

    return false;
}

void hopcroftKarp() {
    bool ok;
    do {
        ok = false;
        for(int i = 1; i <= N; i++) {
            checked[i] = false;
        }
        for(int i = 1; i <= N; i++) {
            if(!left[i]) {
                ok |= pairUp(i);
            }
        }
    }while(ok);
}

void Finish() {
    if(Cuplaj < N) {
        printf("-1"); return;
    }

    for(int i = 1; i <= N; i++) {
        if(left[i] != i) {
            int otherLeft = right[i];
            swap(left[i], left[otherLeft]);
            swap(right[left[i]], right[left[otherLeft]]);
            Sol.push_back(make_pair(i, otherLeft));
        }
    }

    printf("%d\n", (int)Sol.size());
    for(vector< pair< int,int > >::iterator it = Sol.begin(); it != Sol.end(); it++) {
        printf("L %d %d\n", it->first, it->second);
    }
}

int main() {
    readInput();
    hopcroftKarp();
    Finish();

    return 0;
}
