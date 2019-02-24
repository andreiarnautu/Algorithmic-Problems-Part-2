// How about a coding trick?
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#define MOD_1 10007
#define MOD_2 100003
#define MOD_3 6007
#define coef 13
using namespace std;

FILE *fin=freopen("zimeria.in","r",stdin);
FILE *fout=freopen("zimeria.out","w",stdout);
ofstream out("zimeria.out");

int n, val[30], V[400400], k, car[15];
char S[15], sir[15];

void Set()
{
    int i, cif;
    for(i = 0; i < 12; ++i)
    {
        cif = S[i] - 'a';
        val[ cif ] = i + 1;
        car[ i + 1 ] = S[i];
    }
}

void Solve1()
{
    int i, j, ansCount = 0, hashVal_1, hashVal_2, cif, nr;
    for(i = 1; i <= n; ++i)
    {
        gets(sir);
        hashVal_1 = hashVal_2 = 0;
        nr = 0;
        for(j = 4; j >= 0; --j)
        {
            cif = sir[j] - 'a';
            cif = val[ cif ];
            nr = nr * coef + cif;
        }

        if( !V[nr] )
        {
            ++ansCount;
            V[nr] = 1;
        }
    }
    printf("%d", ansCount);
}

void Solve2()
{
    int i, j, cif, nr, x;
    char c;

    for(i = 1; i <= n; ++i)
    {
        gets(sir);
        nr = 0;

        for(j = 0; j < 5; ++j)
        {
            cif = val[ sir[j] - 'a' ];
            nr = nr * coef + cif;
        }
        ++V[nr];
    }
    int ii, INIT = coef * coef * coef * coef;
    string afis;
    for(i = 0; i <= 400000; ++i)
    {
         if( V[i] )
         {
            ii = i;
            x = INIT; afis.clear();
            for(j = 0; j < 5; ++j)
            {
                nr = ii / x;
                c = car[ nr ];
                ii -= nr * x;
                x /= coef;
                afis += c;
            }
            while( V[i] )
            {
                --V[i];
                out << afis << "\n";
            }
         }
    }

}

int main()
{
    int op;
    scanf("%d ", &op);
    scanf("%d ", &n);
    gets(S);
    Set();

    if( op == 1 )
        Solve1();
    else
        Solve2();
    return 0;
}
