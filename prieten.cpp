#include <fstream>
#include <cmath>
using namespace std;
ifstream in("prieten.in");
ofstream out("prieten.out");
unsigned long long n,k;
unsigned long long s;
int main()
{
    long i;
    unsigned long long a,b;
    in>>n>>k>>s;
    for(i=1;i<=k;i++)
        out<<n*i+i<<" ";
    out<<'\n';
    s*=2;
    a=sqrt(double(s));
    a=sqrt(double(a));
   // out<<s*2<<endl;
    for(b=a;(b-2)*(b-1)*b<=s;b++)
    {
       // out<<b*(b-1)*(b-2)<<" ";
        if((b-2)*(b-1)*b==s)
        {
            out<<b-1;
            break;
        }
    }
    return 0;
}
