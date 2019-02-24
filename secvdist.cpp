#include <cstdio>
#include <deque>

using namespace std;

FILE *fin=freopen("secvdist.in","r",stdin);
FILE *fout=freopen("secvdist.out","w",stdout);

deque <int> Dmin, Dmax;
int n, k, lmax, marime, last = 0;
int v[1000013];

int main()
{
    scanf("%d%d", &n, &k);
    lmax = 0;
    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &v[i]);

        while( !Dmin.empty() && v[i] < v[Dmin.back()] )
            Dmin.pop_back();
        Dmin.push_back(i);

        while( !Dmax.empty() && v[i] > v[Dmax.back()] )
            Dmax.pop_back();
        Dmax.push_back(i);

        if( v[Dmax[0]] - v[Dmin[0]] <= k )
        {
            if( i - last > lmax )
                lmax = i - last;
        }

        else
        {
            if( Dmax[0] < Dmin[0] )
            {
                last = Dmax[0];
                Dmax.pop_front();
            }

            else if( Dmax[0] > Dmin[0] )
            {
                last = Dmin[0];
                Dmin.pop_front();
            }

            else
            {
                last = Dmin[0];
                Dmin.pop_front();
                Dmax.pop_front();
            }

            if( v[Dmax[0]] - v[Dmin[0]] <= k )
            {
                if( i - last > lmax )
                    lmax = i - last;
            }
        }
    }

    printf("%d", lmax);
    return 0;
}
