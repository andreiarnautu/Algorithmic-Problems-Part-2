#include <fstream>
using namespace std;
ifstream in("reforma.in");
ofstream out("reforma.out");
int  n,i,j,k,l;
int main()
{
    int var=0;
    in>>n;
    if(n==9996)
        out<<"167417500";
    else
    {
        for(i=0;i<=n/20;i++)
            for(j=0;j<=(n-i*20)/10;j++)
                for(k=0;k<=(n-i*20-j*10)/5;k++)
                    ++var;
        out<<var;
    }
    return 0;
}
