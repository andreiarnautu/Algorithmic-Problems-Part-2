#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("rezervatie.in");
ofstream g("rezervatie.out");
int l,c,n,a[205][205],lin,col,sol[10005];
char ch[10005],cc;

void citire()
{
    f>>l>>c>>ch>>n;
}
void make_m()
{

    lin=1;col=1;
    for(int i=0;i<=strlen(ch)-1;i++)
    {
        if(ch[i]=='E') col++;
        if(ch[i]=='V') col--;
        if(ch[i]=='N') {lin--;a[lin][col]++;}
        if(ch[i]=='S') {a[lin][col]++;lin++;}
    }

    for(int i=1;i<=l;i++)
    {
        for(int j=1;j<=c;j++)
        {
            a[i][j]+=a[i][j-1];
        }
    }
}
void solve()
{
    for(int i=1;i<=n;i++)
    {
        f>>lin>>col;

        if(a[lin][col]%2==1) {sol[0]++;sol[sol[0]]=i;}
    }
}

int main()
{
    citire();
    make_m();
    solve();
    g<<sol[0]<<"\n";
    for(int i=1;i<=sol[0];i++)
    {
       g<<sol[i]<<" ";
    }


    return 0;
}
