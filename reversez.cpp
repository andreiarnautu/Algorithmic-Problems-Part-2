/*
    How about a coding trick?
*/
#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#define PII pair<int,int>
#define MOD 666013
#define DIM 300100
#define buffDIM 100000

using namespace std;
FILE *fin=freopen("reversez.in","r",stdin);
FILE *fout=freopen("reversez.out","w",stdout);

int Father[DIM], Members[DIM], v[DIM];
char buff[buffDIM + 10];
bool viz[DIM];
int n, sigma, pos;
vector <int> Enemies[DIM];
vector <int>::iterator it;
multiset <PII> myset;
queue <int> Q;

void read(int &nr)
{
    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == buffDIM )
            {pos = 0; fread(buff, 1, buffDIM, stdin);}

    nr = 0;
    while( buff[pos] >= '0' && buff[pos] <= '9' )
    {
        nr = nr * 10 + buff[pos] - '0';
        if( ++pos == buffDIM )
            {pos = 0; fread(buff, 1, buffDIM, stdin);}
    }
}

inline int Group(int nod)
{
    if( nod != Father[nod] )
        Father[nod] = Group( Father[nod] );
    return Father[nod];
}

inline void Unite(int x, int y)
{
    x = Group(x);
    y = Group(y);
    if( x == y )
        return;
    Father[y] = x;
}

inline void BFS()
{
    long long int sol = 1, curent;
    int nod;

    Q.push(1);
    while( !Q.empty() )
    {
        nod = Q.front(); Q.pop();
        if( viz[nod] )
            continue;
        viz[nod] = true;
        curent = sigma;

        for(it = Enemies[nod].begin(); it != Enemies[nod].end(); ++it)
        {
            if( viz[*it] )
                --curent;
            else
                Q.push(*it);
        }
        sol = (sol * curent) % MOD;
    }
    printf("%lld", sol);
}

int main()
{
    int i, j, x, g1, g2;

    fread(buff, 1, buffDIM, stdin);

    read( n ); read( sigma );

    //scanf("%d %d ", &n, &sigma);

    for(i = 1; i <= n; ++i)
        Father[i] = i, Members[i] = 1;

    for(i = 1; i <= n; ++i)
    {
        read( x );
       // scanf("%d", &x);
        v[i] = x;
        for(j = i; j < i + x; ++j)
            Unite(j - i + 1, j);
    }


    for(i = 1; i <= n; ++i)
    {
        g1 = 1 + v[i];
        g2 = i + v[i];
        if( g1 > n || g2 > n )
            continue;
        g1 = Group( g1 );
        g2 = Group( g2 );
        if( myset.find( make_pair(g1, g2) ) ==  myset.end() )
        {
            myset.insert( make_pair(g1, g2) );
            myset.insert( make_pair(g2, g1) );
            Enemies[g1].push_back(g2);
            Enemies[g2].push_back(g1);
        }
    }
    BFS();
    return 0;
}
