#include<fstream>
#include<cstdlib>
using namespace std;

int n,i,j,m;

struct poz
{
    short int x,y;
};
poz w[1002];
short int s[1002][1002];

int compare(const void *a, const void *b)
{
    poz x,y;
    x=*(poz*)a;
    y=*(poz*)b;
    if (x.y==y.y) return x.x-y.x;
    return x.y-y.y;
}

int main()
{
    //complexitate O(n^2)
    ifstream fin("riglef.in");
    ofstream fout("riglef.out");

    fin>>n;
    for (i=1;i<=n;i++)
    {
        fin>>w[i].y;
        w[i].x=i;
    }
    qsort(w+1,n,sizeof(poz),compare);
    m=0;
    for (i=2;i<=n;i++)
    {
        for (j=1;j<=i-1;j++)
        {
            if(w[j].x<w[i].x)
                s[i][w[j].x]=1+s[j][w[i].x+1];
                else
                s[i][w[j].x]=1+s[j][w[i].x-1];
        }
        for (j=n;j>w[i].x;j--)
            if(s[i][j+1]>s[i][j])
                s[i][j]=s[i][j+1];
        for (j=1;j<w[i].x;j++)
            if(s[i][j-1]>s[i][j])
                s[i][j]=s[i][j-1];
        for (j=1;j<=n;j++)
        {
            if(s[i][j]>m)
            {
                m=s[i][j];
            }
        }
    }
    fout<<m<<endl;
	fin.close();
    return 0;
}


