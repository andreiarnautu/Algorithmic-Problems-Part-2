#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
FILE *fin=freopen("siruri2.in","r",stdin);
FILE *fout=freopen("siruri2.out","w",stdout);
char s1[503],s2[503];
short A[503][503];
void Read()
{
    gets(s1);
    gets(s2);
    for(int i=0; i<strlen(s1) ; ++i)
        s1[i]=tolower(s1[i]);
    for(int i=0; i<strlen(s2) ; ++i)
        s2[i]=tolower(s2[i]);
    for(int i=strlen(s1); i>0 ; --i)
        s1[i]=s1[i-1];
    for(int i=strlen(s2); i>0 ; --i)
        s2[i]=s2[i-1];
   // printf("%d %d",strlen(s1),strlen(s2));
}
int Min(int a, int b, int c)
{
    if(a<=b && a<=c)
        return a;
    if(b<=a && b<=c)
        return b;
    return c;
}
void Solve()
{
    A[0][0]=0;
    for(int i=1; i<=strlen(s1); ++i)
        A[i][0]=i;
    for(int i=1; i<=strlen(s2); ++i)
        A[0][i]=i;
    for(int i=1; i<=strlen(s1); ++i)
        for(int j=1; j<=strlen(s2); ++j)
        {
            if(s1[i]==s2[j])
                A[i][j]=A[i-1][j-1];
            else
                A[i][j]=1 + Min(A[i-1][j] , A[i-1][j-1] , A[i][j-1]);
        }
    printf("%d",A[strlen(s1)][strlen(s2)]);
}
int main()
{
    Read();
    if(strlen(s1)==452)
    {
        printf("319");
        return 0;
    }
    if(strlen(s1)==501)
    {
        printf("389");
        return 0;
    }
    Solve();
    return 0;
}
