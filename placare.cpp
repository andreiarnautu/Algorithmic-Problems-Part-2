#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#define DIM 303
using namespace std;
FILE *fin=freopen("placare.in","r",stdin);
FILE *fout=freopen("placare.out","w",stdout);

short int A[DIM][DIM];
int n, m;
char S[2000];
string str;

void Solve(int lin)
{
    int i, p = 1, lg, val, j ;
    gets(S);
    lg = strlen(S);

    str.clear();

    for(i = 0; i < lg; ++i)
    {
        if( S[i] != ' ' && S[i] != '\n' )
            str += S[i];
        else
        {
            val = atoi(str.c_str());
            for(; p <= m; ++p)
                if( !A[lin][p] )
                {
                    if( val < 0 )
                        for(j = lin; j < lin - val; ++j)
                            A[j][p] = -val;
                    else
                        for(j = p; j < p + val; ++j)
                            A[lin][j] = val;
                    break;
                }
            str.clear();
        }
    }
    if( !str.empty() )
    {
        val = atoi(str.c_str());
        for(; p <= m; ++p)
                if( !A[lin][p] )
                {
                    if( val < 0 )
                        for(j = lin; j < lin - val; ++j)
                            A[j][p] = -val;
                    else
                        for(j = p; j < p + val; ++j)
                            A[lin][j] = val;
                    break;
                }
        str.clear();
    }
}

int main()
{
    scanf("%d%d ", &n, &m);
    for(int i = 1; i <= n; ++i)
        Solve(i);
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    return 0;
}
