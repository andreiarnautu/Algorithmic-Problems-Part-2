#include <fstream>
#include <cstring>
#include <deque>
#define MaxN 1000013
using namespace std;

ifstream in("trompeta.in");
ofstream out("trompeta.out");

int m, n, l = -1, r = -1;
int nr[MaxN];
char s[MaxN];
char St[MaxN];


void Read()
{
    in >> n >> m; in.get();
    in.get(s, sizeof(s));
}

void Solve()
{
    int i, len, c, num = 0;
    bool ok;

    len = strlen(s);

    for(i = 0; i < len; ++i)
    {
        c = s[i];
        while( r - l > 0 && c > St[r] && num + len - i - 1 >= m )
        {
            --r;
            --num;
        }
        if( num < m )
        {
            St[++r] = c;
            ++num;
        }
    }

    out << St;
}

int main()
{
    Read();
    Solve();
    return 0;
}
