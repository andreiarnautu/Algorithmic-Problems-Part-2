// How about a coding trick?
#include <fstream>
using namespace std;
ifstream in("z.in");
ofstream out("z.out");

inline long long int Nr(int x, int y, int n)
{
    long long int ret = 0;
    if( x > (1 << (n - 1)) )
    {
        ret += 2LL * (1 << (n - 1)) * (1 << (n - 1));
        x -= (1 << (n - 1));
    }
    if( y > (1 << (n - 1)) )
    {
        ret += 1LL * (1 << (n - 1)) * (1 << (n - 1));
        y -= (1 << (n - 1));
    }

    if(n > 1)
    {
        --n;
        ret += Nr(x, y, n);
    }
    return ret;
}

int main()
{
    int n, k, x, y;
    in >> n >> k;

    for(; k > 0; --k)
    {
        in >> x >> y;
        out << Nr(x, y, n) + 1 << "\n";
    }

    return 0;
}
