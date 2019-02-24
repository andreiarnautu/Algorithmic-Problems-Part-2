#include <fstream>
using namespace std;
ifstream in("scaune.in");
ofstream out("scaune.out");

int main()
{
    int n,p=1;
    in>>n;
    for(int i=1;i<2*n;i+=2)
    {   p*=i; p=p%30103;}
    out<<p%30103;
    return 0;
}
