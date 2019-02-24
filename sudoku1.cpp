#include <fstream>
#define L 35

using namespace std;

ifstream f("sudoku1.in");
ofstream g("sudoku1.out");

int n,a[L][L],i,j,u[4][4],v[4];

unsigned long long k,x; // unsigned long long 18,446,744,073,709,551,615

int main()
{
	f>>n>>k;
	x=(1<<n-1);
	x=x*x;
    g<<x*3<<'\n';
    u[1][1]=2;u[1][2]=3; u[2][1]=1;u[2][2]=3; u[3][1]=1;u[3][2]=2;
    //primul element
    if(k<=x)a[1][1]=1;
        else if(k<=2*x)a[1][1]=2,k-=x;
             else a[1][1]=3,k-=2*x;
    //prima linie
    for(j=2;j<=n;j++)
    { x=x/2;
      if(k<=x) a[1][j]=u[a[1][j-1]][1];
        else a[1][j]=u[a[1][j-1]][2], k=k-x;
    }
    //prima coloana
    for(i=2;i<=n;i++)
    { x=x/2;
      if(k<=x) a[i][1]=u[a[i-1][1]][1];
        else a[i][1]=u[a[i-1][1]][2], k=k-x;
    }

    for(i=2;i<=n;i++)
      for(j=2;j<=n;j++)
        { v[1]=v[2]=v[3]=0;
          v[a[i-1][j]]=a[i-1][j];
          v[a[i][j-1]]=a[i][j-1];
          v[a[i-1][j-1]]=a[i-1][j-1];
          a[i][j]=6-v[1]-v[2]-v[3];
          if(a[i][j]==0)a[i][j]=a[i-1][j-1];
        }

   for(i=1;i<=n;i++)
    {for(j=1;j<=n;j++) g<<a[i][j]<<' ';
     g<<'\n';
    }

    f.close();g.close();
    return 0;
}
