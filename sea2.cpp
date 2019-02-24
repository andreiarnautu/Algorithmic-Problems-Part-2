#include <cstdio>
#include <set>
using namespace std;
FILE *fin=freopen("sea2.in","r",stdin);
FILE *fout=freopen("sea2.out","w",stdout);

set< pair<int,int> > vapor;
set< pair<int,int> >::iterator it, it1, it2;

void Solve()
{
    int x, y, n, i;
    scanf("%d ", &n);

    for(i = 1; i <= n; ++i)
    {
        scanf("%d %d ", &x, &y);
        it = vapor.upper_bound(make_pair(x, y));

        if( it != vapor.end() && it -> second > y )
        {
            printf("-1\n"); continue;
        }

        if( !vapor.empty() )
        {
            for(it1 = it2 = it, --it1; it2 != vapor.begin() && it1 -> second < y ; it2 = it1, --it1);

            vapor.erase(it2, it);
        }
        vapor.insert(make_pair(x, y));
        printf("%d\n", vapor.size());
    }
}

int main()
{
    Solve();
    return 0;
}
