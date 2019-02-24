#include <cstdio>
#include <deque>

using namespace std;

FILE *fin=freopen("secventa.in","r",stdin);
FILE *fout=freopen("secventa.out","w",stdout);

int n, k, start, finish, val = -30003, point;
int V[500003];
deque <int> D;
char s[4000003];



void Read_New(int pos)
{
    int aux = 0, semn;

    if( s[point] == '-' )
    {
        semn = -1;
        ++point;
    }
    else
        semn = 1;

    while( 48 <= s[point] && s[point] <= 57 )
    {
        aux = aux * 10 + s[point] - 48;
        ++point;
    }

    ++point;

    V[pos] = aux * semn;
}

int main()
{
    scanf("%d%d", &n, &k);
    getchar();
    gets(s);

    for(int i = 1 ; i <= n ; ++i )
    {
        Read_New(i);
        while( !D.empty() && V[D[D.size() - 1]] > V[i] )
            D.pop_back();
        D.push_back(i);
        while( i - D[0] >= k )
            D.pop_front();
        if(i >= k)
            if( V[D[0]] > val )
            {
                val = V[D[0]];
                finish = i;
                start = i - k + 1;
            }
    }

    printf("%d %d %d", start, finish, val);

    return 0;
}
