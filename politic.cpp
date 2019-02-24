#include <fstream>
#define MaxN 20013

using namespace std;

ifstream in("politic.in");
ofstream out("politic.out");

int V[MaxN], P[MaxN], N, nr, Sum[MaxN], cnt;


void Read()
{
    int first;
    in >> N;
    for(int i = 1 ; i <= N ; ++i )
        in >> V[i];

    first = 1;
    for(int i = 2 ; i <= N ; ++i )
    {
        if( V[i] - V[i - 1] > 1 )
        {
            P[++nr] = i - first;
            first = i;
        }
    }

    P[++nr] = N + 1 - first;

}

void Solve()
{
    out << nr << "\n";

    for(int i = 1 ; i <= nr ; ++i )
        Sum[i] = P[i] + Sum[i - 1];

    int last = 1;
    for(int i = 1; i <= nr ; ++i )
    {
        while( 2 * (Sum[last] - Sum[i - 1] ) <= N && last <= nr )
            ++last;
        if( last > nr )
            break;
        cnt += nr - last + 1;
    }

    out << cnt;
}

int main()
{
    Read();
    Solve();
}
