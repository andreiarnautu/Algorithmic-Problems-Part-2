#include <fstream>
using namespace std;
ifstream in("reactivi.in");
ofstream out("reactivi.out");
short v1[8001],v2[8001];
int n,fr=1,minim;
void pozitie(int p,int u,int &k)
{
    int i,j,di,dj,aux;
    i=p;
    j=u;di=0;dj=-1;
    while(i<j)
    {
        if(v1[i]>v1[j])
        {
            aux=v1[i];
            v1[i]=v1[j];
            v1[j]=aux;
            aux=v2[i];
            v2[i]=v2[j];
            v2[j]=aux;
            aux=di;
            di=-dj;
            dj=-aux;
        }
    i=i+di;
    j=j+dj;
    }
    k=i;
}
void quick(int p,int u)
{
    int k;
    if(p<u)
    {
        pozitie(p,u,k);
        quick(p,k-1);
        quick(k+1,u);
    }
}
int main()
{
    int i;
    in>>n;
    for(i=1;i<=n;i++)
        in>>v1[i]>>v2[i];
    quick(1,n);
    minim=v2[1];
    for(i=2;i<=n;i++)
    {
        if(minim<v1[i])
        {
            ++fr;
            minim=v2[i];
        }
        else if(v2[i]<minim)
            minim=v2[i];
    }
    out<<fr;
    return 0;
}
