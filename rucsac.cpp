#include <cstdio>
#include <vector>
#include <algorithm>
#define DIM 10010
using namespace std;
FILE *fin=freopen("rucsac.in","r",stdin);
FILE *fout=freopen("rucsac.out","w",stdout);

vector < pair<int,int> > V;
int DP[DIM];
int n, gmax;

void Read()
{
    int i, x, y;
    scanf("%d %d", &n, &gmax);

    for(i = 1; i <= n; ++i)
    {
        scanf("%d %d", &x, &y);
        V.push_back(make_pair(x , y));
    }
}

void Solve()
{
    int val, i, j, summax = 0, ans = 0;

    for(i = 0; i < n; ++i)
    {
        val = min(gmax - V[i].first, summax);
        for(j = val; j >= 0; --j)
            if( DP[j + V[i].first] < DP[j] + V[i].second )
            {
                DP[j + V[i].first] = DP[j] + V[i].second;
                ans = max( ans, DP[j + V[i].first] );
            }
        summax += V[i].first;
    }
    printf("%d", ans);
}

int main()
{
    Read();
    Solve();
    return 0;
}
