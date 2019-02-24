#include <cstdio>
#define NMax 25
#define DMax 11
int n, k, D;
int a[NMax][DMax];
int sol[NMax];
int uz[DMax];

FILE *fout;
void read();
void solve();
void write();

int main()
{
 fout=fopen("pluricex.out","w");
 read();
 solve();
 fclose(fout);
 return 0;
}

int verif()
{
int i, j;
for (i=1; i<=D; i++) uz[i]=0;
for (i=1; i<=k; i++)
    for (j=1; j<=D; j++)
        if (a[sol[i]][j]) uz[j]=1;
for (i=1; i<=D; i++)
    if (!uz[i]) return 0;
return 1;
}

void solve()
{
int i;
for (i=1; i<=k; i++) sol[i]=i;
while (1)
      {if (verif()) write();
       for (i=k; i>0 && sol[i]==n-k+i; i--);
       if (!i) break;
       sol[i]++;
       for (i++; i<=k; i++) sol[i]=sol[i-1]+1;
      }
}

void read()
{
 int i, nr, d, j;
 FILE * fin = fopen("pluricex.in", "rt");
 fscanf(fin, "%d %d %d", &n, &k, &D);
 for (i=1; i<=n; i++)
     {fscanf (fin,"%d",&nr);
      for (j=1; j<=nr; j++)
          {fscanf (fin, "%d",&d);
          a[i][d]=1;}
      }
 fclose(fin);
}


void write()
{
int i;
for (i=1; i<k; i++)
    fprintf(fout,"%d ",sol[i]);
fprintf(fout,"%d\n",sol[k]);
}
