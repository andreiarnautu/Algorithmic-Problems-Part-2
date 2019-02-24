#include <fstream>
using namespace std;

ifstream in("suma.in");
ofstream out("suma.out");

long long int n, p, sum;

int main()
{
    int i;
    in >> n >> p;

    for(i = 1; i <= p ; ++i)
        sum = (sum + i * (i - 1)) % p;
    sum = (sum * (n / p)) % p;
    for(i = 1; i <= n % p ; ++i)
        sum = (sum + i * (i - 1)) % p;
    out << sum;

    return 0;
}
