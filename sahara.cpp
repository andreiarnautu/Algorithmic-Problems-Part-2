/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <bitset>
#include <algorithm>

#define buffDim 10010
#define Dim 1010
#define mp make_pair
#define fi first
#define se second

using namespace std;
FILE *fin=freopen("sahara.in","r",stdin);
FILE *fout=freopen("sahara.out","w",stdout);

int add[Dim][Dim], sol[Dim][Dim];
int n, m, Q, T, pos, k;
char buff[buffDim];

bitset <Dim> v[Dim];
queue < pair<int,int> > C;

void read(int &nr) {

    nr = 0;
    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == buffDim ) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }

    while( buff[pos] >= '0' && buff[pos] <= '9' ) {

        nr = nr * 10 + buff[pos] - '0';
        if( ++pos == buffDim ) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }
}

void read_data() {

    int x1, x2, y1, y2, q;
    read(n); read(m); read(Q); read(T);
    for(int i = 1; i <= T; ++i) {

        read(x1); read(y1); read(x2); read(y2); read(q);
        add[x1][y1] += q;
        add[x1][y2 + 1] -= q;
        add[x2 + 1][y1] -= q;
        add[x2 + 1][y2 + 1] += q;
    }
}

void build_solution() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {

            sol[i][j] = sol[i - 1][j] + sol[i][j - 1] - sol[i - 1][j - 1] + add[i][j];
            v[i][j] = (sol[i][j] >= Q);
        }
}

void check(int x, int y) {

    int X, Y;
    C.push( mp(x,y) ); v[x][y] = 0;
    while( !C.empty() ) {

        ++k;
        X = C.front().fi; Y = C.front().se; C.pop();

        if( v[X + 1][Y] ) {
            v[X + 1][Y] = 0;
            C.push( mp(X + 1, Y) );
        }

        if( v[X - 1][Y] ) {
            v[X - 1][Y] = 0;
            C.push( mp(X - 1, Y) );
        }

        if( v[X][Y + 1] ) {
            v[X][Y + 1] = 0;
            C.push( mp(X, Y + 1) );
        }

        if( v[X][Y - 1] ) {
            v[X][Y - 1] = 0;
            C.push( mp(X, Y - 1) );
        }
    }
}

void find_max() {

    int best = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if( v[i][j] ) {

                k = 0;
                check(i, j);
                best = max(best, k);
            }
    printf("%d", best);
}

int main() {

    read_data();
    build_solution();
    find_max();
    return 0;
}
