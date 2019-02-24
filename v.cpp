#include <fstream>
using namespace std;
ifstream in("v.in");
ofstream out("v.out");
int m,n,mat[102][102],p1,p2;
long long s,smax,nr=99999;
int minim(int a,int b)
{
    if(a>=b)
        return a;
    return b;
}
int main()
{
    int j,i,x,l1;
    in>>m>>n;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            in>>mat[i][j];
    for(i=0;i<n-1;i++)
    {
        x=minim(m-1,(n-1-i)/2);
        s=0;
        for(l1=1;l1<=x;l1++)
        {
            s=0;
            for(j=i;j<=l1+i;j++)
                s+=mat[j-i][j];
            for(j=l1+i;j<=i+2*x;j++)
                s+=mat[2*x+i-j][j];
            out<<s<<endl;
            if(s>smax || (smax==s && l1<nr))
            {
                smax=s;
                nr=l1;
                p1=l1;
                p2=i+l1;
            }
        }
    }
    out<<smax<<" "<<p1+1<<" "<<p2+1;
    return 0;
}
