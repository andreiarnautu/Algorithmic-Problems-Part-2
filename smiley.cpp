#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("smiley.in","r",stdin);
FILE *fout=freopen("smiley.out","w",stdout);

char S[300], c = '1', Pattern[] = ":;>8", Pattern2[] = "[]()DPOX3" ;
int ansCount, pos;
bool ok;

int main()
{

    while( c != NULL )
    {
        c = NULL;
        scanf("%s%c", &S, &c);
        if( c == NULL )
            break;
        pos = 0;
        while( pos < strlen(S) )
        {
            if(strchr(Pattern, S[pos]))
                {
                    ++pos;
                    while( pos < strlen(S) && S[pos] == '-' )
                        ++pos;
                    if( pos < strlen(S) && strchr(Pattern2, S[pos]) )
                    {
                        ++ansCount;
                        while( pos < strlen(S) && S[pos] == S[pos - 1] )
                            ++pos;
                    }
                }
            else
                ++pos;
        }
        S[0] = NULL;
    }

    printf("%d", ansCount);
    return 0;
}
