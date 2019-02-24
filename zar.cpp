#include <fstream>
using namespace std;
ifstream f("zar.in");
ofstream g("zar.out");
int st_dr[4],sus_jos[4],f1,f2,f3;
long n,k;
void afis(int st_dr[])
{   int i;
	//cout<<endl;
	//for(i=1;i<=4;i++)
	//  cout<<st_dr[i]<<"  ";
}
void rostogolire_dreapta(int st_dr[],long p)
{   int i,j,aux;
	p=p%4;
	for(i=1;i<=p;i++)
	{
		aux=st_dr[1];
		for(j=1;j<=3;j++)
			st_dr[j]=st_dr[j+1];
		st_dr[4]=aux;
	}
}


void rostogolire_stanga(int st_dr[],long p)
{   int i,j,aux;
	p=p%4;
	for(i=1;i<=p;i++)
	{
		aux=st_dr[4];
		for(j=4;j>=1;j--)
			st_dr[j]=st_dr[j-1];
		st_dr[1]=aux;
	}
}

int main()
{
f>>n>>k;
f>>f1>>f2>>f3;

st_dr[1]=7-f2; st_dr[2]=f3; st_dr[3]=f2; st_dr[4]=7-f3;
sus_jos[1]=7-f2;sus_jos[2]=f1;sus_jos[3]=f2;sus_jos[4]=7-f1;

while(k>0)
{
	if (k<n)//dreapta
		{rostogolire_dreapta(st_dr,k);k=0;}
		else
		{rostogolire_dreapta(st_dr,n-1);k=k-(n-1);}

	sus_jos[1]=st_dr[1];sus_jos[3]=st_dr[3];

	if (k<n)//jos
		{rostogolire_dreapta(sus_jos,k);k=0;}
		else
		{rostogolire_dreapta(sus_jos,n-1);k=k-(n-1);}

	 st_dr[1]=sus_jos[1];st_dr[3]=sus_jos[3];

	if (k<n)//stanga
		{rostogolire_stanga(st_dr,k);k=0;}
		else
		{rostogolire_stanga(st_dr,n-1);k=k-(n-1);}

	sus_jos[1]=st_dr[1];sus_jos[3]=st_dr[3];

	if (k<n)//sus
		{rostogolire_stanga(sus_jos,k);k=0;}
		else
		{rostogolire_stanga(sus_jos,n-1);k=k-(n-1);}
	 st_dr[1]=sus_jos[1];st_dr[3]=sus_jos[3];



}
g<<sus_jos[2]<<" "<<st_dr[3]<<" "<<st_dr[2];

	return 0;
}
