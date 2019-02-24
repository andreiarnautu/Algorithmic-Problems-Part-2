/**
  *  Worg
  *  Backtracking pentru descoperirea formulei
  */
#include <cstdio>

using namespace std;

#define inFile      "regine.in"
#define outFile     "regine.out"

using namespace std;

int n, max;
bool m[20][20];

void back(int k, int l, int c) {

    if(c > l)
        return;
    if(l > n)
        return;

    bool ok = 1;
    for(int i = 1; i < l && i < c; ++i)
        if(m[l - i][c - i])
            ok = 0;
    for(int i = 1; l + i <= n && c + i <= n; ++i)
        if(m[l + i][c + i])
            ok = 0;
    for(int i = 1; l - i > 0; ++i)
        if(m[l - i][c])
            ok = 0;
    for(int i = 1; l + i <= n; ++i)
        if(m[l + i][c])
            ok = 0;
    for(int i = 1; c - i > 0; ++i)
        if(m[l][c - i])
            ok = 0;
    for(int i = 1; c + i <= l; ++i)
        if(m[l][c + i])
            ok = 0;

    if(ok) {

        m[l][c] = 1;
        if(max < k) {

            max = k;
            printf("%d\n", k);
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= i; ++j)
                    if(m[i][j])
                        printf("%d %d\n", i, j);
            printf("------------");
        }
        if(c == l)
            back(k + 1, l + 1, 1);
        else
            back(k + 1, l, c + 1);
        m[l][c] = 0;
    }
    else {

        if(c == l)
            back(k, l + 1, 1);
        else
            back(k, l, c + 1);
    }
}

int main() {

    freopen(inFile, "r", stdin);
    freopen(outFile, "w", stdout);
    scanf("%d ", &n);

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            back(1, i, j);
    return 0;
}
