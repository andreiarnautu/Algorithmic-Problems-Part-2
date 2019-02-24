#include <fstream>
using namespace std;
ifstream in("unupatru.in");
ofstream out("unupatru.out");
int n;
long long x,f[10000];
int efect(long long p)
{
    long long pp,nr=0;
    while(p!=4 && p!=1)
    {
        pp=0;
        ++nr;
        while(p)
        {
            pp+=(p%10)*(p%10);
            p=p/10;
        }
        p=pp;
    }
    return nr;
}
int main()
{
    in>>n;
    for(short i=0;i<n;i++)
    {
        in>>x;
        out<<efect(x)<<" ";
    }
    return 0;
}
