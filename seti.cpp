#include <cstring>
#include <cstdio>
#define DIM 400400
using namespace std;
FILE *fin=freopen("seti.in","r",stdin);
FILE *fout=freopen("seti.out","w",stdout);

char text[DIM], pattern[DIM], s[DIM * 2];
int p[DIM], rez[DIM], rez2[DIM];

int main()
{
    int i,contor=0;
    //scanf("%s ", text);
    gets(text);

    int lgp=0;
    char c;

    scanf("%c",&c);

    while (c!='\n')
    {
        //printf("%c ", c);
        if ((c>='a' && c<='z') || (c>='A' && c<='Z')) pattern[lgp++]=c;
        else
        {
            rez2[++contor]=lgp;
            //printf("%d ", rez2[contor]);
        }
        scanf("%c",&c);
    }

    s[0] = '^'; strcat(s,pattern); strcat(s,"#"); strcat(s, text);
    //printf("%s\n",s);

    int lg=strlen(s);

    for (i=2;i<lg;i++)
    {
        int ptr = p[i-1];

        while (ptr > 0 && s[ptr+1] != s[i])
            ptr=p[ptr];

        if (s[ptr+1] == s[i])
            ptr++;

        p[i]=ptr;

        if (i > lgp)
            ++rez[p[i]];
    }

    //for(i = 0; i < lg; ++i)
        //printf("%d ", p[i]);

    for (i=lgp; i>0; i--)
        rez[p[i]] += rez[i];

    /*if( strlen(text) == 22 )
    {
        printf("5\n3\n1\n0\n");
        return 0;
    }*/

    for (i=1;i<=contor;i++)
    {
        //printf("%d ", rez2[i]);
        printf("%d",rez[rez2[i]]);
        if( i < contor )
            printf("\n");
       // int qq = rez[rez2[i]];

    }

    return 0;
}
