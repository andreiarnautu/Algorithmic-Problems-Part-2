#include <cstdio>
#define InFile "rez.in"
#define OutFile "rez.out"
#define LMax 1001
int n, p=0;
char s[LMax];
long r;
using namespace std;
void citire(void);
void afisare(void);
long rezserie(void);
long rezparalel(void);

int main()
{
citire();
r=rezserie();
afisare();
return 0;
}

void citire(void)
{
FILE *fin=fopen(InFile, "r");
fscanf(fin,"%s",s);
for (n=0; s[n]; n++);
fclose(fin);
}

void afisare(void)
{
FILE *fout=fopen(OutFile,"w");
fprintf(fout,"%ld\n",r);
fclose(fout);
}

long rezserie()
{
long val, suma=0;
if (p>=n || s[p]==',' || s[p]==')') return 0;
while (p<n && s[p]!=',' && s[p]!=')')
       if (s[p]=='R')
         {p++;
          val=s[p]-'0';
          p++;
          if (s[p]>='0' && s[p]<='9')
             {val=val*10+s[p]-'0';p++;}
          suma+=val;
          }
         else suma+=rezparalel();
return suma;
}

long rezparalel()
{
long suma=0, produs=1, val;
while (s[p]!=')')
      {p++;
       val=rezserie();
       suma+=val; produs*=val;
      }
p++;
return produs/suma;
}
