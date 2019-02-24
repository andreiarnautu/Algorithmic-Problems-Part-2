#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

FILE *fin=freopen("vila2.in","r",stdin);
FILE *fout=freopen("vila2.out","w",stdout);

deque <int> D;
int N, K, V[100013], Size, Max;


int main()
{
    scanf("%d%d", &N, &K);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
    for(int i = 1 ; i <= 1 + K ; ++i )
    {
        for(int j = Size - 1 ; j >= 0 ; --j )
            {
                if( V[D[j]] <= V[i] )
                {
                    --Size;
                    D.pop_back();
                }
                else
                    break;
            }
        ++Size;
        D.push_back(i);
    }
    Max = abs( V[1] - V[D[0]] );

    for(int i = 2 ; i <= N ; ++i )
    {
        if( i + K <= N )
        {
            for(int j = Size - 1 ; j >= 0 ; --j )
            {
                if( V[D[j]] <= V[i + K] )
                {
                    --Size;
                    D.pop_back();
                }
                else
                    break;
            }
            ++Size;
            D.push_back(i + K);
        }
        if( i - D[0] > K )
        {
            --Size;
            D.pop_front();
        }
        if( abs( V[D[0]] - V[i] ) > Max )
            Max = abs( V[D[0]] - V[i] );
    }

    printf("%d", Max);
    return 0;
}
