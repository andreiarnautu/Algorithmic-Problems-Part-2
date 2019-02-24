#include <cstdio>
#define Mod 666013
#define Nmax 1000001
using namespace std;
FILE *fin=freopen("unuzero.in","r",stdin);
FILE *fout=freopen("unuzero.out","w",stdout);
int N, P, Q;

int V[Nmax], A[Nmax], B[Nmax];

int main()
{
    int i;
    scanf("%d%d%d", &N, &P, &Q);
    V[0] = 1;
    B[0] = 1;
    for(int i = 1 ; i <= N ; ++i )
    {
        B[i] = B[i - 1] + A[i - 1];
        B[i] %= Mod;
        if( i >= P )
        {
            if( i > Q )
                A[i] = V[i - P] - V[i - Q - 1];
            else
                A[i] = V[i - P];
        }
        if( A[i] < 0 )
            A[i] += Mod;
        A[i] %= Mod;
        V[i] = (V[i - 1] + B[i]);
        V[i] %= Mod;
    }
   // for(int i = 1 ; i <= N ; ++i )
   //     printf("%d %d %d\n",A[i],B[i],V[i]);
    if( A[N] + B[N] > 0 )
        printf("%d", (A[N] + B[N] - 1) % Mod);
    else
        printf("%d", (A[N] + B[N] - 1 + Mod) % Mod);
    return 0;
}
