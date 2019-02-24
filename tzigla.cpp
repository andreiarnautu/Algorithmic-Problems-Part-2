#include <fstream>
using namespace std;
ifstream in("tzigla.in");
ofstream out("tzigla.out");
long long i,x,y,k;
short ok=0;
int main()
{
    in>>x>>y>>k;
    if(y==k)
    {
        if(x%y==0)
        {
            ok=1;
            out<<y;
        }
    }
    else if((y-k)%(x-k)==0 && x!=k)
    {
        ok=1;
        out<<x;
    }
    else
        for(i=x/2;i>=2;i--)
        {
        if(i<=k)
            break;
        if((y-k)%(i-k)==0 && x%i==0)
        {
            ok=1;
            out<<i;
            break;
        }
        }
    if(ok==0)
        out<<"0";
    return 0;
}
