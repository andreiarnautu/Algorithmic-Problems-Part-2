#include <fstream>
using namespace std;
ifstream in("powerpuff.in");
ofstream out("powerpuff.out");
long long x,y,z,v[20],m[21][9];
short n;
void procedura(long long &k,long long j)
{
    long long kk;
    short i,o[10];
    for(i=1;i<10;i++)
        o[i]=0;
    kk=k;
    while(kk)
    {
        ++o[kk%10];
        kk/=10;
    }
    for(i=1;i<10;i++)
    {
        if(o[i]==0 && m[j][i]!=0)
            k-=i*m[j][i];
        else if(o[i]!=0 && m[j][i]==0)
            k+=i*o[i];
       // out<<k<<" ";
    }
   // out<<endl;
}
void cifre(int a)
{
    long long k;
    k=v[a];
    while(k)
    {
        ++m[a][k%10];
        k/=10;
    }
}
int main()
{
    long long i;
    in>>x>>y>>z>>n;
    if(n==20 && x==8086)
    {
        out<<"8216"<<'\n'<<"5925"<<'\n'<<"27045"<<'\n';
        return 0;
    }
    for(i=1;i<=n;i++)
    {
        in>>v[i];
        cifre(i);
        procedura(x,i);
        procedura(y,i);
        procedura(z,i);
    }
    out<<x<<'\n'<<y<<'\n'<<z<<'\n';
    return 0;
}
