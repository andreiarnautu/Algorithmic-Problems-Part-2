#include <fstream>
#include <cmath>
using namespace std;
ifstream in("proddiv.in");
ofstream out("proddiv.out");
long long a,b;
bool v[500000];
long long nr,p,viz[300000];
void ciur()
{
    long long i,j;
    for(i=4;i<=b/2;i+=2)
        v[i]=1;
    viz[0]=2;
    ++p;
    for(i=3;i<=b/2;i+=2)
        if(!v[i])
        {
            viz[p]=i;
            ++p;
            for(j=i*3;j<=b/2;j+=2*i)
                v[j]=1;
        }
}
void build()
{
    long long i,k=0,j;
    for(i=0;i<p;i++)
    {
        if(viz[i]*viz[i]*viz[i]>=a && viz[i]*viz[i]*viz[i] <=b)
           ++nr;
        if(viz[i]*viz[i]*viz[i]>=b)
            break;
    }
    for(i=0;i<p-1;i++)
        for(j=i+1;j<p;j++)
        {
            if(viz[i]*viz[j]>=a && viz[i]*viz[j]<=b)
                ++nr;
            if(viz[i]*viz[j]>=b)
                break;
        }
    out<<nr<<'\n';
}
int main()
{
    long long i;
    in>>a>>b;
    ciur();
 //   for(i=0;i<p;i++)
  //      out<<viz[i]<<" ";
    build();
    return 0;
}
