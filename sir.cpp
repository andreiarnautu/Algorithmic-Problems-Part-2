#include <fstream>
#include <deque>
#include <algorithm>
#define MaxN 1000013

using namespace std;

ifstream in("sir.in");
ofstream out("sir.out");

int n, x, y, z, last, lmax, p1, p2;
int v[MaxN];
deque <int> Dmin, Dmax;


int main()
{
    in >> n >> x >> y >> z;

    for(int i = 1 ; i <= n ; ++i )
    {
        in >> v[i];

        while( !Dmin.empty() && v[Dmin.back()] >= v[i] )
            Dmin.pop_back();
        Dmin.push_back(i);

        while( !Dmax.empty() && v[Dmax.back()] <= v[i] )
            Dmax.pop_back();
        Dmax.push_back(i);

        if( i < x || i - last + 1 < x)
            continue;

        while( Dmin[0] + y <= i )
            Dmin.pop_front();

        while( Dmax[0] + y <= i )
            Dmax.pop_front();

        while( !Dmax.empty() && !Dmin.empty() && v[Dmax[0]] - v[Dmin[0]] > z )
        {

            if( Dmin[0] < Dmax[0] )
            {
                last = Dmin[0] + 1;
                Dmin.pop_front();
            }

            else if( Dmin[0] > Dmax[0] )
            {
                last = Dmax[0] + 1;
                Dmax.pop_front();
            }

            else
            {
                last = Dmin[0] + 1;
                Dmin.pop_front();
                Dmax.pop_front();
            }
        }

        if(  v[Dmax[0]] - v[Dmin[0]] <= z && lmax <= i - max(last, i - y + 1) + 1 && i - max(last, i - y + 1) + 1 >= x && i - max(last, i - y + 1) + 1 <= y)
        {
            lmax = i - max(last, i - y + 1) + 1;
            p1 = max(last, i - y + 1);
            p2 = i;
        }

    }

    if( lmax > 0 )
        out << lmax << " " << p1 << " " << p2 << " ";
    else
        out << "-1 ";
    return 0;
}
