/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define DIM 1000100

using namespace std;
FILE *fin=freopen("prefix.in","r",stdin);
FILE *fout=freopen("prefix.out","w",stdout);

char S[DIM];
int pi[DIM];
int len;

void Solve()
{
    int i,k = 0;
    gets(S + 1); len = strlen(S + 1);

    for(i = 2; i <= len; ++i)
    {
        while(k && S[i] != S[k + 1])
            k = pi[k];
        if(S[i] == S[k + 1])
            ++k;
        pi[i] = k;
    }
    for(i = len; i > 1; --i)
        if( pi[i] && i % (i - pi[i]) == 0 )
        {
            printf("%d\n", i); return;
        }
    printf("0\n");
}

int main()
{
    int teste;
    for(scanf("%d ", &teste); teste; --teste)
        Solve();
    return 0;
}
