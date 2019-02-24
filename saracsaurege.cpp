/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

#define Dim 50500

using namespace std;
FILE *fin=freopen("saracsaurege.in","r",stdin);
FILE *fout=freopen("saracsaurege.out","w",stdout);

deque < int > D;
int v[Dim], q[Dim];
int n, m, dim = 1;

void update() {

    for(int i = 1; i <= n; ++i) {

        if(!D.empty() && i - D.front() >= dim)
            D.pop_front();

        while(!D.empty() && v[i] > v[D.back()])
            D.pop_back();
        D.push_back(i);

        if(i >= dim)
            q[i] = v[D.front()];
    }
    D.clear();
}

void Set() {

    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%d ", &v[i]);

    while(dim <= n)
        dim <<= 1;
    dim >>= 1;
    update();
}

int main() {

    Set();
    int a, b;
    for(int i = 1; i <= m; ++i) {

        scanf("%d %d ", &a, &b);
        if(dim > b - a + 1) {

            while(dim > b - a + 1)
                dim >>= 1;
            update();
        }
        printf("%d\n", max(q[b], q[a + dim - 1]));
    }
    return 0;
}
