#include <cstdio>
#include <cstring>
#include <fstream>
using namespace std;
//FILE *fin=freopen("spion1.in","r",stdin);
//FILE *fout=freopen("spion1.out","w",stdout);
ifstream in("spion1.in");
ofstream out("spion1.out");
char S[100005];
long long fact[100004];
int Mod = 100003;
void Solve1()
{
    int nr = 1;
    for(int i=0 ; i<Mod ; ++i)
        if( S[i] == 'E' )
            ++nr;
    out<<nr;
}
void Factorial(int x)
{
    fact[0] = 1;
    fact[1] = 1;
    for(int i=2 ; i<= x; ++i)
        fact[i] = ( 1ll * fact[i-1] * i ) % Mod;
}
int Putere(int x, int y)
{
    int p = 1;
    while( y )
    {
        if ( y & 1 )
        {
            p = (1ll * p * x) % Mod;
            y--;
        }
        x = (1ll * x * x)% Mod;
        y >>= 1;
    }
    return p;
}
void Solve2()
{
    int nr = 0;
    long long T;
    Factorial(Mod);
    for(int i=0; i<Mod ; ++i)
        if( S[i] == 'E' )
            ++nr;
    if( !nr )
    {
        out<<1;
        return;
    }
 //   printf("%d %d",nr,strlen(S));
   // for(int i=1 ; i<=strlen(S); ++i)
     //   printf("%d ",fact[i]);
  //  printf("%lld",Putere(2,200));
  //  printf("%d", Putere(2 , Mod-2));
  //  printf("%d",Putere( 1ll * fact[nr] * fact[strlen(S)-nr] % Mod , Mod-2 ));
    T = 1ll * fact[Mod] * Putere( 1ll * fact[Mod] * fact[Mod-nr] % Mod , Mod-2 ) % Mod;
    out<<T;
}
void Read()
{
    int a;
   // scanf("%d",&a);
    //scanf("%s",&S);
    in >> a;
    in.get();
    in.getline(S, Mod);

    if( a == 1 )
        Solve1();
    else
        Solve2();
}
int main()
{
    Read();
    return 0;
}
