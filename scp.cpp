#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("scp.in","r",stdin);
FILE *fout=freopen("scp.out","w",stdout);

char S[2003];
struct {int a, b;} V[2003];
int F[2003];

void Solve()
{
    int L, d = 0, i, j;
    L = strlen(S);
    for(int i = L ; i > 0 ; --i )
        S[i] = S[i - 1];
    for(int i = 1 ; i <= L ; ++i )
    {
        V[i].a = V[i - 1].a, V[i].b = V[i - 1].b;
        if( S[i] == '(' )
            V[i].a++;
        else if( S[i] == ')' )
        {
            V[i].b++;
            if( V[i].b > V[i].a )
            {
                if( d == 0 )
                {
                    printf("IMPOSIBIL");
                    return;
                }
                for( j = i ; j <= L && S[j] == ')' ; ++j )
                F[d] += V[i].b - V[i].a + j - i;
                V[d].a += V[i].b - V[i].a + j - i;
                i = d;
                continue;
            }
        }
        else if( S[i] =='[' )
            d = i;
        else
        {

        }
    }
}

int main()
{
    scanf("%s", &S);
    printf("%s", S);
    Solve();
    return 0;
}
