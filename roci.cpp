#include <cstdio>
using namespace std;
FILE *fin=freopen("roci.in","r",stdin);
FILE *fout=freopen("roci.out","w",stdout);
int N, F[10007], Max, Min=10001;
void Read()
{
    scanf("%d",&N);
    int x;
    for(int i=0; i<N ; ++i)
    {
        scanf("%d",&x);
        if( x > Max )
            Max = x;
        if( x < Min )
            Min = x;
        ++F[x];
    }
}
void Solve()
{
    bool ok=1, g;
    int Nr=0, i, Valmin, j, Maxx;
    while(ok)
    {
        ok = 0;
        i = 1;
        while( i<= 10000 )
        {
            if( F[i] > 0 )
            {
                ok = 1;
                Valmin = F[i];
                j = i;
                while( F[j] > 0 )
                {
                    if( F[j] < Valmin)
                        Valmin = F[j];
                    ++j;
                }
                for(int l=i; l<j ; ++l)
                    F[l] -= Valmin;
                Nr += Valmin;
                i = j;
            }
            ++i;
        }
    }
    printf("%d",Nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
