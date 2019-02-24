#include <cstdio>
#include <cstring>
const int Mod  = 100003;
#define Nmax 100010
using namespace std;
FILE *fin=freopen("spion.in","r",stdin);
FILE *fout=freopen("spion.out","w",stdout);
char S[Nmax];
int Fact[Nmax];

void Process(int a)
{
    Fact[1] = 1;
    for(int i = 2 ; i <= a ; ++i )
        Fact[i] = 1ll * i * Fact[i - 1] % Mod;
}

int Power(int a, int b)
{
    int P = 1;
    while( b )
    {
        if( b & 1 )
            P = 1ll * P * a % Mod;
        a = 1ll * a * a % Mod;
        b >>= 1;
    }
    return P;
}

int Comb(int a, int b)
{
    if( a == 0 || b == 0 )
        return 1;
    Process(a);
    return 1ll * Fact[a] * Power( 1ll * Fact[b] * Fact[a - b] % Mod, Mod - 2) % Mod;
}

int main()
{
    int c, Nr = 0, k;
    scanf("%d", &c);
    getchar();
    gets(S);
    k = strlen(S);
    for(int i = 0 ; i < k ; ++i )
        if( S[i] == 'E' )
            ++Nr;
    if( c == 1 )
        printf("%d", Nr + 1);
    else
        printf("%d", Comb(k , Nr));
    return 0;
}
