#include <cstdio>
using namespace std;
FILE *fin=freopen("pod.in","r",stdin);
FILE *fout=freopen("pod.out","w",stdout);
int L, P, N, V[100001], Max;

void Read()
{
    int i;
    scanf("%d%d%d", &L, &P, &N);
    for( i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
    Max = V[N] - V[1];
}

int Check(int x)
{
    int nr = 1, dist = 0;
    for(int i = 2 ; i <= N ; ++i )
    {
        if( nr >= P )
            return 1;
        dist += V[i] - V[i - 1];
        if( dist >= x )
        {
            ++nr;
            dist = 0;
        }
    }
    if( nr >= P )
        return 1;
    return 0;
}

void Binary_Search()
{
    int st, dr, m, k, kk;
    st = 0;
    dr = Max;
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        k = Check(m);
        if( k )
            st = m;
        else
            dr = m;
    }
    printf("1");
    int dist = 0;
    for(int i = 2 ; i <= N ; ++i )
    {
        dist += V[i] - V[i - 1];
        if( dist < st )
            printf("0");
        else
        {
            dist = 0;
            printf("1");
        }
    }
}

int main()
{
    Read();
    Binary_Search();
    return 0;
}
