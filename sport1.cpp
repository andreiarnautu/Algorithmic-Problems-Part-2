#include <fstream>
#include <iomanip>
using namespace std;
ifstream in("sport1.in");
ofstream out("sport1.out");
short a,b;
long long s,n;
int main()
{
    int k=2,aux;
    in>>b>>a;
    s=a+b;
    in>>n;
    while(k<n)
    {
        if((a==4 && b==4) || (a==3 && b==3))
            {
                b=a;
                a=3;
            }
        else if(a==5 && b==5)
            {
                b=a;
                a=2;
            }
        else if(a!=b && a>b)
            {
                b=a;
            }
        else if(a!=b && a<b)
            {
                aux=a;
                a=b;
                b=aux;
            }
        s+=a;
      //  out<<b<<" "<<a<<endl;
        ++k;
    }
    out.precision(3);
    out<<fixed<<(float)s/n;
    return 0;
}
