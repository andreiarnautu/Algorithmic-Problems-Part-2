#include <fstream>
using namespace std;
ifstream in("puncte2.in");
ofstream out("puncte2.out");

unsigned long long int n;

int main()
{
    in >> n;
    out << n * (n - 1) * (n - 2) * (n - 3) / 24;
    return 0;
}
