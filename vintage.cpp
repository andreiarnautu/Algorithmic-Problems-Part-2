#include <fstream>
using namespace std;
ifstream in("vintage.in");
ofstream out("vintage.out");
int n,k,p[1001],c[1001],poz[1001],castig,pret;
void sorteaza()
{
    int i,j;
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            if(c[i]>c[j] || (c[i]==c[j] && p[i]<p[j]))
            {
                swap(c[i],c[j]);
                swap(p[i],p[j]);
                swap(poz[i],poz[j]);
            }
}
int main()
{
    int i;
    in>>n>>k;
    for(i=1;i<=n;i++)
    {
        in>>p[i]>>c[i];
        poz[i]=i;
    }
    sorteaza();
    for(i=n;i>n-k;i--)
    {
        castig+=c[i];
        pret+=p[i];
    }
    out<<castig<<" "<<pret<<'\n';
    for(i=n;i>n-k;i--)
        out<<poz[i]<<" ";
}
