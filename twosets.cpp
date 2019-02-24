// How about a coding trick?
#include <cstdio>
#include <vector>
#include <cstring>
#define MOD_1 6007
#define MOD_2 100003
#define MOD_3 104003
#define coef 1000000
#define DIM 3000000
using namespace std;
FILE *fin=freopen("twosets.in","r",stdin);
FILE *fout=freopen("twosets.out","w",stdout);

struct trio {
                int r1, r2, r3;
            };

vector <long long int> HASH[MOD_1 + 100];
vector <trio> v;
char S[DIM];


void Solve()
{
    int i, len, q1, q2, q3, cif, ind1 = 0, ind2 = 0, j;
    long long int val;
    int ok;

    trio aux;
    gets(S); len = strlen(S); v.clear();
    aux.r1 = aux.r2 = aux.r3 = 0;
    v.push_back(aux);

    for(i = 0; i <= MOD_1; ++i)
        HASH[i].clear();

    for(i = 0; i < len; ++i)
    {
        if( S[i] == 'i' )
        {
            aux = v.back();
            cif = S[i + 1] - '0';

            q1 = ( aux.r1 * 2 + cif ) % MOD_1;
            q2 = ( aux.r2 * 2 + cif ) % MOD_2;
            q3 = ( aux.r3 * 2 + cif ) % MOD_3;

            aux.r1 = q1, aux.r2 = q2, aux.r3 = q3; v.push_back(aux);
            ++i;
        }
        else if( S[i] == 'd' )
            v.pop_back();

        else
        {
            aux = v.back();
            HASH[aux.r1].push_back( 1LL * aux.r2 * coef + 1LL * aux.r3 );
            ++ind1;
        }
    }

    gets(S); v.clear(); len = strlen(S);
    aux.r1 = aux.r2 = aux.r3 = 0; v.push_back(aux);

    for(i = 0; i < len; ++i)
    {
        if( S[i] == 'i' )
        {
            aux = v.back();
            cif = S[i + 1] - '0';

            q1 = (aux.r1 * 10 + cif) % MOD_1;
            q2 = (aux.r2 * 10 + cif) % MOD_2;
            q3 = (aux.r3 * 10 + cif) % MOD_3;

            aux.r1 = q1, aux.r2 = q2, aux.r3 = q3; v.push_back(aux);
            ++i;
        }
        else if( S[i] == 'd' )
            v.pop_back();
        else
        {
            aux = v.back();
            q1 = aux.r1, q2 = aux.r2, q3 = aux.r3, val = 1LL * q2 * coef + 1LL * q3;

            ok = 0;
            for(j = 0; j < HASH[q1].size(); ++j)
                if( val == HASH[q1][j] )
                    ok = 1;
            if( !ok )
            {
                printf("0\n");
                return;
            }
            ++ind2;
        }
    }
    if( ind1 != ind2 )
    {
        printf("0\n");
        return;
    }
    printf("1\n");
}

int main()
{
    int t;
    for(scanf("%d ", &t); t; --t)
        Solve();
    return 0;
}
