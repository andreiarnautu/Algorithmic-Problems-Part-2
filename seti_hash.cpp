/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <unordered_map>

#define MOD_1 6007
#define MOD_2 9907
#define sigma 57

using namespace std;
FILE *fin=freopen("seti.in","r",stdin);
FILE *fout=freopen("seti.out","w",stdout);

unordered_map < int, int > cnt;
char S[ (1 << 17) + 10 ], aux[70];
int n, m, len;

void Read_Text()
{
    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i)
    {
        gets(aux);
        strcat(S, aux);
    }
    len = 64 * n;
}

int value(char c)
{
    if(c < 'a')
        return c - 'A';
    return c - 'a' + 26;
}

void Introduce(int pos, int k)
{
    int i, nr_1 = 0, nr_2 = 0;
    for(i = pos; i < pos + k; ++i)
    {
        nr_1 = ( nr_1 * sigma + value( S[i] ) ) % MOD_1;
        nr_2 = ( nr_2 * sigma + value( S[i] ) ) % MOD_2;
        cnt[nr_1 + nr_2 * 10000]++;
    }
}

void Query()
{
    int lg, i, nr_1 = 0, nr_2 = 0;
    gets(aux); lg = strlen(aux);

    for(i = 0; i < lg; ++i)
    {
        nr_1 = ( nr_1 * sigma + value( aux[i] ) ) % MOD_1;
        nr_2 = ( nr_2 * sigma + value( aux[i] ) ) % MOD_2;
    }
    printf("%d\n", cnt[nr_1 + nr_2 * 10000]);
}

int main()
{
    Read_Text();
    for(int i = 0; i <= len - 18; ++i)
        Introduce(i, 17);
    for(int i = len - 17; i <= len; ++i)
        Introduce(i, len - i);
    for(scanf("%d ", &m) ; m; --m)
        Query();
}
