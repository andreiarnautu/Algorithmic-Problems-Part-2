/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define Dim 100100 * 3
#define buffDim 50500

using namespace std;
FILE *fin=freopen("sequencequery.in","r",stdin);
FILE *fout=freopen("sequencequery.out","w",stdout);

struct{int best, lBest, rBest, sum;} arb[Dim];
int pos, n, m;
long long int ans, S;
char buff[buffDim];

void read(int &nr) {

    char semn = '+';
    while(buff[pos] < '0' || buff[pos] > '9') {

        semn = buff[pos];
        if(++pos == buffDim) {

            pos = 0;
            fread(buff, 1, buffDim, stdin);
        }
    }
    nr = 0;
    while(buff[pos] >= '0' && buff[pos] <= '9') {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim) {

            pos = 0;
            fread(buff, 1 , buffDim, stdin);
        }
    }
    nr = ((semn == '-')? -nr : nr);
}

void update(int node, int left, int right, int pos, int val) {

    if(left == right) {
        arb[node].best = val, arb[node].lBest = val, arb[node].rBest = val, arb[node].sum = val;
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(pos <= mid)
        update(lSon, left, mid, pos, val);
    if(mid < pos)
        update(rSon, mid + 1, right, pos, val);

    arb[node].best = max(max(arb[lSon].best, arb[rSon].best), arb[lSon].rBest + arb[rSon].lBest);
    arb[node].lBest = max(arb[lSon].lBest, arb[lSon].sum + arb[rSon].lBest);
    arb[node].rBest = max(arb[rSon].rBest, arb[rSon].sum + arb[lSon].rBest);
    arb[node].sum = arb[lSon].sum + arb[rSon].sum;
}

void query(int node, int left, int right, int first, int last) {

    if(left > last || right < first)
        return;
    if(first <= left && right <= last) {
        S = max(S, 0LL);
        ans = max(ans, 1LL * max(S + 1LL * arb[node].lBest, 1LL * arb[node].best));
        S = max(S + 1LL * arb[node].sum, 1LL * arb[node].rBest);
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    query(lSon, left, mid, first, last);
    query(rSon, mid + 1, right, first, last);
}

int main() {

    read(n); read(m);
    int x, y;
    for(int i = 1; i <= n; ++i) {
        read(x);
        update(1, 1, n, i, x);
    }
    for(int i = 1; i <= m; ++i) {
        read(x); read(y);
        ans = -(1 << 20), S = 0;
        query(1, 1, n, x, y);
        printf("%lld\n", ans);
    }
    return 0;
}
