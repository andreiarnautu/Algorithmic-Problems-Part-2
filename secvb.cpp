#include <fstream>
using namespace std;
ifstream in("secvb.in");
ofstream out("secvb.out");
int n,v[50000],v2[1000];
long long t;
int main()
{
    int x,nrsecv=0,i,j,tt;
    long long k;
    in>>n>>t;
    tt=t;
    for(i=1;i<=1000;i++)
    {
        j=i;
        while(j)
        {
            if(j%2==1)
                ++v2[i];
            j=j/2;
        }
    }
    for(i=0;i<n;i++)
    {
        in>>x;
        v[i]=v2[x];
       // out<<v[i]<<" ";
    }
   // out<<t<<endl;
    t=tt;

    for(i=0;i<n;i++)
    {
        k=v[i];
        j=i+1;
        while(j<n && k<t)
        {
            k+=v[j];
            j++;

        }
        if(k==t)
            ++nrsecv;
    }
    out<<nrsecv;
    return 0;
}
