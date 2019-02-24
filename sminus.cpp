#include <fstream>
using namespace std;
ifstream in("sminus.in");
ofstream out("sminus.out");
long long n,p1,p2,i1;
int v[100001];
long long suma,s,smax;
int main()
{
    long long i;
    in>>n;
    in>>v[0];
    p1=0;p2=0;s=v[0]; i1=0; smax=s; suma=v[0];
    for(i=1;i<n;i++)
    {
        if(s<0)
        {
            i1=i;
            s=0;
        }
        in>>v[i];
        suma+=v[i];
        s+=v[i];
        if(s>smax)
        {
            smax=s;
            p1=i1;
            p2=i;
        }
        else if(s==smax && p1==i1)
        {
            smax=s;
            p2=i;
        }
    }
 //   out<<suma<<endl;
    out<<p1+1<<" "<<p2+1<<'\n';
    for(i=p1;i<=p2;i++)
        suma-=2*v[i];
    out<<suma;
    return 0;
}
