#include <fstream>
using namespace std;
ifstream in("policefm.in");
ofstream out("policefm.out");
long long p,f[10];
short i;
int main()
{
    in>>p;
    if(p!=0)
    {
        for(i=0;i<10;i++)
        f[i]=0;
    for(i=9;i>1;i--)
        while(p%i==0)
          {
            p/=i;
            ++f[i];
          }
    if(p!=1)
        out<<"0";
    else
        for(i=2;i<10;i++)
            while(f[i]!=0)
            {
                out<<i;
                --f[i];
            }
    }
    else
        out<<"10";
    return 0;
}
