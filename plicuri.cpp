#include <fstream>
using namespace std;
ifstream in("plicuri.in");
ofstream out("plicuri.out");
long long n,i,l[100000],w[100000],j,aux,nrc,nrmax;
int main()
{
    in>>n;
    for(i=0;i<n;i++)
        in>>l[i]>>w[i];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(l[i]>l[j] || (l[i]==l[j] && w[i]<w[j]))
            {
                aux=l[i];
                l[i]=l[j];
                l[j]=aux;
                aux=w[i];
                w[i]=w[j];
                w[j]=aux;
            }
    nrc=1;
    for(i=n-2;i>=0;i--)
    {
        if(l[i]>l[i+1] && w[i]>w[i+1])
            ++nrc;
        else
        {
            out<<i<<endl;
            if(nrc>nrmax)
                nrmax=nrc;
            nrc=1;
        }
    }
    out<<nrmax;
    return 0;
    return 0;
}
