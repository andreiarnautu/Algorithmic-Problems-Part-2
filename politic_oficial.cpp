#include<cstdio>

#define InFile "politic.in"
#define OutFile "politic.out"
using namespace std;
int p[15001],N,K,sum[14001];

int main()
{
 int N1,i,j,nr,xc,xp;
 long coalitii;

 freopen(InFile,"r",stdin);
 freopen(OutFile,"w",stdout);

 /* citesc datele si formez coalitiile */
 scanf("%d",&N);
 scanf("%d",&xp);
 K = 0;
 nr = 1;
 for (i=1;i<N;i++)
    {
     scanf("%d",&xc);
     if (xc == xp+1) nr++;
      else
	 {
	  p[K++] = nr;
	  nr = 1;
	 }
     xp = xc;
    }
  p[K++] = nr;
 /* Calculez numarul de coalitii */
 N1 = N/2;
 nr = p[0];
 i = 0;
 j = 0;
 coalitii = 0;
 p[K] = 0;
 while (i<K)
   {
    if (nr>N1)
	{
	 coalitii += (K-i);
	 nr -= p[j];
	 j++;
	}
      else {i++;nr+=p[i];}
   }
 printf("%d %ld\n",K,coalitii);

 return 0;
}
