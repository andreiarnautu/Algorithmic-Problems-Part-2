#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin = freopen("vocale.in","r",stdin);
FILE *fout = freopen("vocale.out","w",stdout);
int N;
char s[300], S[300][300], Voc[]={'a','e','i','o','u'}, M[600][600];
int Nr[300];

void Search(int k)
{
    char *ch;
    bool ok;
    char kk[600], chr[600];
    int nr, Min = 1000, Sol = 0, q;
    ch = strtok(s," ");
    while( ch != NULL )
    {
        nr = 0;
        for(int i = 0 ; i < strlen(ch) ; ++i )
            if( strchr(Voc,ch[i]) != NULL)
                ++nr;
        if(nr < Min)
        {
            Min = nr;
            Sol = 1;
            S[k][0] = strlen(ch);
            for(int i = 1 ; i <= strlen(ch); ++i )
                S[k][i] = ch[i - 1];
            strcpy(M[Sol],ch);
        }
        else if( nr == Min )
        {
            ok = 1;
            for(int i = 1; i <= Sol ; ++i )
                if( strcmp(M[i],ch) == 0 )
                {
                    ok = 0;
                    break;
                }
            if( ok )
            {
                ++Sol;
                strcpy(M[Sol],ch);
            }
        }
        ch = strtok( NULL, " ");
    }
    Nr[k] = Sol;
}

void Read()
{
    scanf("%d", &N);
    getchar();
    for(int i = 1 ; i <= N ; ++i )
    {
        gets(s);
        Search(i);
    }
    for(int i = 1; i <= N ; ++i )
    {
        for(int j = 1; j <= S[i][0] ; ++j )
            printf("%c",S[i][j]);
        if(i < N)
            printf(" ");
    }
    printf("\n");
    int Output = 1;
    for(int i = 1 ; i <= N ; ++i )
        Output = (Output * Nr[i]) % 2003;
    printf("%d\n", Output);
}

int main()
{
    Read();
    return 0;
}
