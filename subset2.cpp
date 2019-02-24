#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("subset2.in");
ofstream out("subset2.out");



int main()
{
    int n, k, nr, c, r, sol;
    in >> n >> k;

    if( k % 2 == 0 )
        {
            nr = k / 2 - 1;
            sol = 2;
            c = n / k;
            r = n % k;

            sol += c * nr;

            sol += min( nr, r );
        }

    else
        {
            nr = k / 2;
            sol = 1;

            c = n / k;
            r = n % k;

            sol += c * nr;
            sol += min( nr, r );
        }

    out << sol;

    return 0;
}
