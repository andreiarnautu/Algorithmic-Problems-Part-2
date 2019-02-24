#include <fstream>
using namespace std;
ifstream in("turn.in");
ofstream out("turn.out");
long long n,i,nrc,j;
short ok=1,k,v[49000],f[9];
int main()
{
    in>>n>>k;
    for(i=0;i<n;i++)
        in>>v[i];
    while(ok)
    {
        ok=0;
        nrc=0;
        for(i=1;i<n;i++)
        {
            if(v[i]==v[i-1])
            {
                if(nrc==0)
                    nrc=2;
                else
                    ++nrc;
            }
            else
            {
                if(nrc>=k)
                {
                    ok=1;
                    for(j=i-nrc;j<=n-nrc;j++)
                        v[j]=v[j+nrc];
                    n-=nrc;
                }
                nrc=0;
               // for(i=0;i<n;i++)
             //       out<<v[i]<<" ";
             //   out<<'\n';
            }
            if(i==n-1 && nrc>=k)
            {
                ok=1;
                n-=nrc;
            }
           // out<<nrc<<endl;
            if(ok)
                break;
        }
    }
    out<<n<<endl;
    for(i=0;i<n;i++)
        out<<v[i]<<" ";
    return 0;
}
