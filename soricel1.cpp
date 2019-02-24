#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("soricel1.in");
ofstream out("soricel1.out");
int m,n,mat[201][201],a[500][2],d[500][2],nra,nrd,poz,x1,x2;
void cerinte()
{
    int i,distmin=4000,n1,n2,maxim;
    for(i=nrd;i>=1;i--)
    {
        n1=abs(a[poz][1]-d[i][1]);
        n2=abs(a[poz][2]-d[i][2]);
        if(n1>n2)
            maxim=n1;
        else
            maxim=n2;
        if(maxim<=distmin)
        {
            distmin=maxim;
            x1=i;
        }
    }
    out<<x1<<endl;
    distmin=4000;
    for(i=nra;i>=1;i--)
    {
        n1=abs(d[x1][1]-a[i][1]);
        n2=abs(d[x1][2]-a[i][2]);
        if(n1>n2)
            maxim=n1;
        else
            maxim=n2;
        if(maxim<=distmin)
        {
            distmin=maxim;
            x2=i;
        }
    }
    out<<x2;
}
int main()
{
    int i;
    in>>m>>n;
    in>>nra;
    for(i=1;i<=nra;i++)
        in>>a[i][1]>>a[i][2];
    in>>nrd;
    for(i=1;i<=nrd;i++)
        in>>d[i][1]>>d[i][2];
    in>>poz;
    cerinte();
    return 0;
}
