/*
    How about a coding trick?
*/
#include <cstdio>
#define zeros(x) ((x ^ (x - 1)) & x)
#define DIM 30030
using namespace std;
FILE *fin=freopen("schi.in","r",stdin);
FILE *fout=freopen("schi.out","w",stdout);

int AIB[DIM], v[DIM], ans[DIM];
int n;

inline void Add(int pos, int val)
{
    int i;
    for(i = pos; i <= n; i += zeros(i))
        AIB[i] += val;
}

inline int Query(int pos)
{
    int i, ret = 0;
    for(i = pos; i; i -= zeros(i))
        ret += AIB[i];
    return ret;
}

int main()
{
    int i, j, p2, sol;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &v[i]);
        Add(i, 1);
    }

    for(p2 = 1; p2 < n; p2 <<= 1);

    for(i = n; i; --i)
    {
        sol = 0;
        for(j = p2; j; j >>= 1)
            if(j + sol <= n && Query(sol + j) < v[i])
                sol += j;
        ans[++sol] = i;
        Add(sol, -1);
    }


    for(i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
