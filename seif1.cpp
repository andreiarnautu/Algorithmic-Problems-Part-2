#include <fstream>
using namespace std;
ifstream in("seif1.in");
ofstream out("seif1.out");
int v[200],m[100][100],n,kk,k;

void umplerev()
{
    int i,j;
    for(i=0;i<n/2;i++)
        {
            v[k]=m[i][n/2-1-i];
            ++k;
        }
    for(i=n/2;i<n;i++)
        {
            v[k]=m[i][i-n/2];
            ++k;
        }
    for(i=n-1;i>=n/2;i--)
        {
            v[k]=m[i][n-i+n/2-1];
            ++k;
        }
    for(i=n/2-1;i>=0;i--)
        {
            v[k]=m[i][n+i-n/2];
            ++k;
        }
    --k;
}

void mutari()
{
    int i,aux;
    while(kk)
    {
        --kk;
        aux=v[0];
        for(i=0;i<k;i++)
            v[i]=v[i+1];
        v[k]=aux;
    }
}
void afisare()
{
    for(int i=0;i<=k;i++)
        out<<v[i]<<" ";
}

int main()
{
    in>>n>>kk;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            in>>m[i][j];
    umplerev();
    mutari();
    afisare();
    return 0;
}
