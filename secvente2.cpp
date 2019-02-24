#include <cstdio>
using namespace std;
FILE *fin=freopen("secvente2.in","r",stdin);
FILE *fout=freopen("secvente2.out","w",stdout);


int N, V[200003], S[1000010];


void Read()
{
    scanf("%d",&N);
    for(int i=1; i<=N ; ++i)
        scanf("%d",&V[i]);
}
void Solve()
{
    int Max = 0, st, dr;
    for(int i=1; i<=N ; ++i)
    {
        st = V[i];
        dr = V[i];
        if( S[V[i]-1] != 0 )
            st = S[V[i]-1];
        if( S[V[i]+1] != 0)
            dr = S[V[i]+1];
        S[st] = dr;
        S[dr] = st;
        if( Max < dr - st + 1 )
            Max = dr - st + 1;

        printf("%d\n",Max);
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
