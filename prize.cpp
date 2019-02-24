#include <fstream>
using namespace std;
ifstream in("prize.in");
ofstream out("prize.out");
int n;
long long x;
int main()
{
    in>>n;
    long long s;
    s=1-n;
    for(int i=1;i<=n;i++)
    {
        in>>x;
        s+=x;
    }
    out<<s;
    return 0;
}
