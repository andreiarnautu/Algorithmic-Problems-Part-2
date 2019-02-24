	
/**
  *   Worg
  */
#include <cstdio>

#define DIM 100100	
#define i64 long long int
#define lsb(x) ((x ^ (x - 1)) & x)

using namespace std;
	
FILE *fin=freopen("farfurii.in","r",stdin);	 FILE *fout=freopen("farfurii.out","w",stdout);
	
int AIB[DIM];
int n;
i64 k;

int Query(int pos)	
{
    int i, ret = 0;	
    for(i = pos; i; i -= lsb(i))
        ret += AIB[i];
    return ret;
}

void Add(int pos, int val)	
{
    int i;
    for(i = pos; i <= n; i += lsb(i))
        AIB[i] += val;
}
	
int Find(int x)	
{
    int st = 1, dr = n, m, ret = n;
		
    while(st <= dr)
    {
        m = (st + dr) >> 1;
        if( Query(m) >= x )
            dr = m - 1, ret = m;
        else
            st = m + 1;
    }
	
    return ret;
}

int main()	
{
    scanf("%d %lld", &n, &k);	
    for(int i = 1; i <= n; ++i)
        AIB[i] = lsb(i);
    i64 rest;
    int ans;

    for(int i = 1; i <= n; ++i)
    {
        rest = 1LL * (n - i) * (n - i - 1) / 2;
        if(rest > k)
        {
            ans = Find(1);
            printf("%d ", ans);
            Add(ans, -1);
        }
	
        else
        {
            ans = Find(k - rest + 1);
            printf("%d ", ans);
            Add(ans, -1);
            k = rest;
        }
    }
	
    return 0;
}