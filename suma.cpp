#include <fstream>
using namespace std;
ifstream in("suma.in");
ofstream out("suma.out");
int n,v1[1000],v2[1000];

int main()
{
    int i,nn,ok=1;
    in>>n;
    nn=n-1;
    v1[0]=1;
    i=n-1;
    while(nn && ok)
    {
        if(nn>9)
        {
            v1[i]=9;
            nn-=9;
        }
        else
        {
            v1[i]=nn;
            ok=0;
        }
        i--;
    }
    i=0;
    ok=1;
    nn=n;
    while(nn && ok)
    {
        if(nn>9)
        {
            v2[i]=9;
            nn-=9;
        }
        else
        {
            v2[i]=nn;
            ok=0;
        }
        ++i;
    }
    for(i=0;i<n;i++)
        out<<v1[i];
    out<<endl;
    for(i=0;i<n;i++)
        out<<v2[i];
    return 0;
}
