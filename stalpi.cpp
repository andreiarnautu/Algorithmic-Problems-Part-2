#include <cstdio>
using namespace std;
FILE *fin=freopen("stalpi.in","r",stdin);
FILE *fout=freopen("stalpi.out","w",stdout);
int N, S[20000], K, P;

void Read()
{
    scanf("%d%d%d", &N, &K, &P);

    int x;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &x);
        S[x] = 0;
    }
}

int main()
{
    Read();

    return 0;
}
