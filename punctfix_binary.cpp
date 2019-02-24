#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("punctfix.in","r",stdin);
FILE *fout=freopen("punctfix.out","w",stdout);
int N, K;
long V[10001];
void Read()
{
    scanf("%d",&N);
    for(int i=1 ; i<=N; ++i)
    {
        scanf("%d",&V[i]);
        V[i] = i - V[i];
    }
}
void Solve()
{
    int st, dr, m, nr;
    long x;
    scanf("%d",&K);
    for(int i=1; i<=K ; ++i)
    {
        scanf("%d",&x);
        st = 1;
        nr = 0;
        dr = N;
        while( st + 1 < dr )
        {
            m = (st + dr) / 2;
            if( V[m] > x )
                dr = m;
            else if( V[m] == x )
            {
                st = m;
                dr = m + 1;
                break;
            }
            else
                st = m;
        }
       // if( V[st+1] == x )
        //    ++nr;
        for(int j=st; j>0 ; --j)
        {
            if( V[j] == x )
                ++nr;
            else
                break;
        }
        for(int j=dr; j<=N ; ++j)
        {
            if( V[j] == x )
                ++nr;
            else
                break;
        }
        printf("%d\n",nr);
    }
}
int main()
{
    Read();
    sort(V+1,V+N+1);
    Solve();
}
