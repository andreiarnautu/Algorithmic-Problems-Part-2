#include <fstream>
using namespace std;
ifstream in("porumb.in");
ofstream out("porumb.out");

int v[100];

void citire(int n)
{
    for(int i=0;i<n;i++)
        in>>v[i];
}

int main()
{
    int n,m,s=0;
    in>>n>>m;
    citire(n);
    for(int i=0;i<n;i++)
        s+=v[i];
    if(m==n || m==1)
        s+=n-1;
    else if(n-m > m-1)
        s+=n-1+m-1;
    else if(m-1>=n-m)
        s+=n-1+n-m;
    out<<s;
    return 0;
}
