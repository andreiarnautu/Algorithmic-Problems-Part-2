#include <fstream>
#include <cmath>
using namespace std;
ifstream in("secvente1.in");
ofstream out("secvente1.out");
int d;
long v[15000];
short f[30000];
long long n,p,k;
void ciur()
{
    float r; r=sqrt(double(30000));
    long i,j;
    for(i=1;i<=30000;i++)
        f[i]=1;
    i=1;
    while(i<=r)
    {
        do
        {
            ++i;
        }while(!f[i]);
        j=i*2;
        while(j<=30000)
        {
            f[j]=0;
            j+=i;
        }
    }
}
int verifica(long y)
{
    if(y==1)
        return 0;
    while(y%p==0)
        y/=p;
    if(f[y])
        return 1;
    return 0;
}
int main()
{
    long long point,j,x,i;
    in>>d;
    ciur();
   // for(i=1;i<=30000;i++)
     //   out<<f[i]<<" ";
    p=5;
    for(i=0;i<d;i++)
    {
        in>>n>>p>>k;
        point=0;
        for(j=1;j<=n;j++)
        {
            in>>x;
            if(verifica(x))
            {
                ++point;
                v[point]=j;
            }
        }
       // for(j=1;j<=point;j++)
         //   out<<v[j]<<" ";
        //out<<endl;
      //  out<<point<<endl<<endl;
        if(point-k+1>0)
            out<<point-k+1<<'\n';
        else
            out<<"0"<<'\n';
        for(j=1;j<=point-k+1;j++)
            out<<v[j]<<" "<<v[j+k-1]<<'\n';
    }
    return 0;
}
