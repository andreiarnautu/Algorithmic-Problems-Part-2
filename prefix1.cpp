#include <fstream>
#include <cstdlib>
using namespace std;
ifstream in("prefix1.in");
ofstream out("prefix1.out");
char c;
int k,s,p,f[100],maxim,putere=1;
int main()
{
    in>>k;
    while(!in.eof())
    {
        in>>c;
        p=c-48;
      //  out<<p<<endl;
        s=(p+10*s)%k;
        ++f[s];
        if(f[s]>maxim)
            maxim=f[s];
    }
    if(f[s]==maxim)
    {
        --f[s];
        --maxim;
    }
    for(int i=0;i<k;i++)
        if(f[i]==maxim)
        {
            out<<i<<" "<<f[i];
            break;
        }
    return 0;
}
