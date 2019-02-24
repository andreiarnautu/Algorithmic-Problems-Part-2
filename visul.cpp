#include<cstdio>
#include<cmath>
#include <fstream>
using namespace std;
ifstream in("visul.in");
ofstream out("visul.out");
unsigned long formula;
unsigned int i,n,nr,pus[100];
int main()
{
printf("n=");

//fflush(stdin);
in>>n;
formula=n;
if((n==1)||(n==10)) out<<"-1";
else
{
for(i=1;i<100;i++)pus[i]=0;
int nrcifre=n-1,bun;
do
{       bun=0; nr=formula%10;
        i=1;
        while((i<10)&&(!bun))
        { nr=nr*10+i;
          int prim=1;
          if(nr<=1)prim=0;
          else for(int j=2;j<=sqrt(double(nr));j++)
                if(!(nr%j))prim=0;
          if((prim)&&(!pus[nr]))
                {pus[nr]=1;
                formula=formula*10+i;
                bun=1;
                nrcifre--;
                }
                else nr/=10;

          i+=2;
          }
}while(nrcifre);
out<<formula;
}
}
