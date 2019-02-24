#include <cstdio>
using namespace std;
FILE *fin=freopen("poly.in","r",stdin);
FILE *fout=freopen("poly.out","w",stdout);
#define Max 30103
int N;
long long C[555];

void Read()
{
    scanf("%d",&N);
}

void Solve()
{
    C[0] = 1;
    for(int i=1; i<=N ; ++i)
        for(int j=0; j<i ; ++j)
            C[i] = ( C[i] % Max + ( C[j] * C[i-j-1] ) % Max ) % Max;
    printf("%d",C[N]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
