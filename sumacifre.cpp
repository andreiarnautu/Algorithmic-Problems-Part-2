#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
ifstream in("sumacifre.in");
ofstream out("sumacifre.out");
long long n,s;
int k,v1[8];
int main()
{
    int i=0,p=0,x=0;
    in>>n>>k;
    while(n)
    {
        v1[i]=n%10;
        n/=10;
        i++;
        ++p;
    }
    while(k)
    {
        for(i=p-1;i>x;i--)
            v1[i]=abs(v1[i]-v1[i-1]);
        if(x<p-1)
            ++x;
        while(v1[p-1]==0)
            --p;
        for(i=x;i<p;i++)
            {
                s=s+pow((double)10,i-x)*v1[i];
            }
        --k;
    }
    out<<s;
    return 0;
}
