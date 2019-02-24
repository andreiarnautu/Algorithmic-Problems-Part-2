#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("rv.in","r",stdin);
FILE *fout=freopen("rv.out","w",stdout);

char S[103], N;
int p1, p2;

void Min()
{
    char c1, c2;
    c1 = S[p1];
    c2 = S[p2];
    for(int i = p1 ; i <= p2 - (i - p1) ; ++i )
    {
        if( S[i] < S[p2 - i + p1] )
        {
            printf("%c",c1);
            ++p1;
            return;
        }
        else if( S[i] > S[p2 - i + p1] )
        {
            printf("%c",c2);
            --p2;
            return;
        }
        else if( i == p2 - i + p1 || i == p2 - i + p1 - 1 )
        {
            printf("%c",c1);
            ++p1;
            return;
        }
    }
}

void Max()
{
    char c1, c2;
    c1 = S[p1];
    c2 = S[p2];
    for(int i = p1 ; p2 - (i - p1) >= i ; ++i )
    {
        if( S[i] > S[p2 - i + p1] )
        {
            printf("%c",c1);
            ++p1;
            return;
        }
        else if( S[i] < S[p2 - i + p1] )
        {
            printf("%c",c2);
            --p2;
            return;
        }
        else if( i == p2 - i + p1 || i == p2 - i + p1 - 1 )
        {
            printf("%c",c1);
            ++p1;
            return;
        }
    }
}

int main()
{
    scanf("%s", &S);
    N = strlen(S) ;
    p1 = 0;
    p2 = N - 1;
    for(int i = 1 ; i <= N ; ++i )
    {
        if( i % 2 == 0 )
            Min();
        else
            Max();
    }
    return 0;
}
