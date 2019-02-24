#include <fstream>
#include <cstring>
using namespace std;
ifstream in("prime.in");
ofstream out("prime.out");
int v[50000],p[8000];
long long nr;
char s[6000];
void ciur()
{
    int i,j,k=1;
    for(i=4;i<=50000;i+=2)
        v[i]=1;
    for(i=3;i<=50000;i+=2)
        if(v[i]==0)
            for(j=2*i;j<=50000;j+=i)
                v[j]=1;
    for(i=2;i<=50000;i++)
        if(v[i]==0)
        {
            p[k]=i;
            ++k;
        }
}
void sursa()
{
    for(int i=0;i<=strlen(s);i++)
        if(s[i]=='1')
            nr+=p[i+1];
    out<<nr;
}
int main()
{
    in.get(s,sizeof(s));
    ciur();
    sursa();
    return 0;
}
