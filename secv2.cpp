#include <cstdio>

using namespace std;

FILE *fin=freopen("secv2.in","r",stdin);
FILE *fout=freopen("secv2.out","w",stdout);

int Sum[50013], N, K, x, Min = 2000000000, first, last, p, Smax = -2000000000;

int main()
{
    scanf("%d%d", &N, &K);

    for(int i = 1 ; i < K ; ++i )
        {
            scanf("%d", &x);
            Sum[i] = Sum[i - 1] + x;
        }

    for(int i = K ; i <= N ; ++i )
        {
            scanf("%d", &x);
            Sum[i] = Sum[i - 1] + x;

            if( Sum[i - K] < Min )
                {
                    Min = Sum[i - K];
                    p = i - K + 1;
                }

            if( Sum[i] - Min > Smax )
                {
                    Smax = Sum[i] - Min;
                    first = p;
                    last = i;
                }

        }

    printf("%d %d %d", first, last, Smax);

    return 0;
}
