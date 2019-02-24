#include <fstream>
#include <cstdlib>

int a[11], s1max[11], s2max[11], solutii=0, Smax=0;


ifstream f("numere.in");
ofstream g("numere.out");

void citire()
{
  int i;
  for (i=1; i<=10; i++) f>>a[i];
  f.close();
}

void rezolva()
{
  int  vi[11]={0,0,0,0,0,0,0,0,0,0,0}, vj[11]={0,0,0,0,0,0,0,0,0,0,0};
  int i, ii, j, k, x, gasit, si, sj, jj, disjuncti;
  int cati1;

  for(ii=1; ii<=1022; ii++)
    {
      i=10;
      while(vi[i]) vi[i--]=0;      //adun 1 la vi
      vi[i]=1;

      si=0;
      for (i=1; i<=10; i++)
	  if (vi[i]) si+=a[i];
      for (i=1; i<=10; i++) vj[i]=vi[i];
      for (jj=ii+1; jj<=1022; jj++)
	{
	  j=10;
	  while(vj[j]) vj[j--]=0;  //adun 1 la vj
	  vj[j]=1;

	  sj=0;
	  for(j=1; j<=10; j++)
	    if(vj[j]) sj+=a[j];

	  if(si==sj)
	    {
	      disjuncti=1;
	      for(k=1; k<=10; k++)
		if((vi[k]+vj[k])==2)
		  disjuncti=0;
	      if(disjuncti)
		{
		  solutii++;
	          if (si>Smax)
		      {
			Smax=si;
			for (i=1; i<=10; i++) s1max[i]=vi[i];
			for (i=1; i<=10; i++) s2max[i]=vj[i];
		      }
		}
	    }
	}
    }
}

void afisare()
{
  int i;
  g<<solutii<<" "<<Smax<<endl;
  for(i=1; i<=10; i++)
    if (s1max[i]) g<<a[i]<<' ';
  g<<endl;
  for(i=1; i<=10; i++)
    if (s2max[i]) g<<a[i]<<' ';
  g<<endl;
  g.close();
}

void main()
{
  citire();
  rezolva();
  afisare();
}
