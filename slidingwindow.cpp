#include <algorithm>
#include <fstream>
#define Dim 1000001

using namespace std;

ifstream in("slidingwindow.in");
ofstream out("slidingwindow.out");

int N, D, Min = 2000000002;
struct Duo{int a, b;} V[Dim];


inline bool cmp(Duo x, Duo y)
{
    return( x.b < y.b );
}

void Check(int k)
{
    for(int j = k - 1 ; j > 0 ; --j )
    {
        if( abs( V[j].a - V[k].a ) <= D )
        {
            if( abs( V[j].b - V[k].b ) <= Min )
                Min = abs( V[j].b - V[k].b );
            return;
        }

        if( abs( V[j].b - V[k].b ) > Min )
            return;
    }
}

int main()
{
    in >> N >> D;

    for(int i = 1 ; i <= N ; ++i )
    {
        in >> V[i].b;
        V[i].a = i;
    }

    sort( V + 1 , V + N + 1 , cmp);

    for(int i = 1 ; i <= N ; ++i )
    {
        Check(i);
        if( Min == 0 )
            break;
    }

    out << Min;
    return 0;
}
