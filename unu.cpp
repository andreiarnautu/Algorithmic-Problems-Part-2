#include <cstdio>
using namespace std;
FILE *fin=freopen("unu.in","r",stdin);
FILE *fout=freopen("unu.out","w",stdout);
int N, V[200005];
void Solve()
{
    int i,t=0;
    for(i=1; i<2*N || t; ++i, t/=10)
    {
        if(i<=N)
            V[i]=(t+=i)%10;
        else
            V[i]=(t+=2*N-i)%10;
    }
    for(int j=i-1; j>0 ; j--)
        printf("%d",V[j]);
}
int main()
{
    scanf("%d",&N);
    Solve();
    return 0;
}
