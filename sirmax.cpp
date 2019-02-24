 #include <cstdio>
using namespace std;
FILE *fin= freopen("sirmax.in", "r", stdin);
FILE *fout= freopen("sirmax.out", "w", stdout);

int N, V[101], Best[101], Last[101][101], Max = 1, V2[101];

void Write(int k, int V1[])
{
    int q;
    ++V1[0];
    V1[V1[0]] = k;
    if( V1[0] >= Max )
    {
        for(int i = 1 ; i <= V1[0] ; ++i )
            printf("%d ",V1[i]);
        printf("\n");
    }
    else
    {
        q = V1[0];
        for(int i = 1 ; i <= Last[k][0] ; ++i )
        {
            Write(Last[k][i], V1);
            V1[0] = q;
        //    printf("*");
        }
    }
}

void Solve()
{
    Best[N] = 1;
    int KK[101];
    for(int i = N - 1 ; i > 0 ; --i )
    {
        for(int j = i + 1 ; j <= N ; ++j )
        {
            if( V[j] > V[i] && Best[i] < Best[j] + 1 )
            {
                Best[i] = Best[j] + 1;
                Last[i][0] = 1;
                Last[i][1] = j;
            }
            else if( V[j] > V[i] && Best[i] == Best[j] + 1 )
            {
                ++Last[i][0];
                Last[i][Last[i][0]] = j;
            }
        }
        if( Best[i] == 0 )
            Best[i] = 1;
        if( Best[i] > Max )
            Max = Best[i];
    }
    for(int i = 1 ; i <= N ; ++i )
        if( Best[i] == Max )
        {
            KK[0] = 0;
          //  V1[1] = i;
            Write(i, KK);
        }
}

int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
    Solve();
    return 0;
}
