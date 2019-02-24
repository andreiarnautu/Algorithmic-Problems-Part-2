#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("spioni.in");
ofstream out("spioni.out");
short mat[12000][12000];
int n,v[1000],k=0;
long long l,x,y,p1=10000,p2=10000;
char s[100001];
void cauta()
{
    int a,b;
    a=p1-1;b=p2-1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
      //  out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1-1;b=p2;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
      //  out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1-1;b=p2+1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
       // out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1;b=p2-1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
      //  out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1;b=p2;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
        out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1;b=p2+1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
      //  out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1+1;b=p2-1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
        out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1+1;b=p2;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
       // out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
    a=p1+1;b=p2+1;
    if(mat[a][b]!=0)
    {
        v[mat[a][b]]=1;
      //  out<<v[k]<<" ";
        mat[a][b]=0;
        ++k;
    }
}
int main()
{
    long long i;
    in>>n;
    for(i=0;i<n;i++)
    {
        in>>x>>y;
        mat[y+10000][x+10000]=i+1;
    }
    in>>l;
    in.get();
    in.get(s,l+1);
    for(i=0;i<l;i++)
    {
        if(s[i]=='N')
            ++p1;
        else if(s[i]=='S')
            --p1;
        else if(s[i]=='E')
            ++p2;
        else if(s[i]=='V')
            --p2;
        cauta();
    }
    //sort(v,v+k);
    for(i=0;i<1000;i++)
        if(v[i]==1)
            out<<i<<'\n';
    if(k==0)
        out<<"-1";
    return 0;
}
