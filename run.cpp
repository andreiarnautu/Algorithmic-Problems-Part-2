# include<cstdio>
# include<algorithm>
# include<fstream>
using namespace std;
//FILE *f=freopen("input.in","r",stdin);
//FILE * g=freopen("input.out","w",stdout);
ifstream f("run.in");
ofstream g("run.out");

int a[100][100];
int main()
{
    int i,j,n,maxim=0,m;
    char x;
    //scanf("%d%d",&n,&m);>
    f>>n>>m;
    for( i = 0 ; i <= n - 1; i++)
        for ( j = 0 ; j<= m - 1; j++)
    {
        f>>x;
        //f.get(x);
        //scanf("%c",&x);
        if(x == '.')
            a[i][j] = 1 + max(a[i - 1][j] , a[i][j - 1]);
        if( x == '&') a[i][j] = 0;
    }
     for( i = 0 ; i <= n - 1; i++)
        for ( j = 0 ; j<= m - 1; j++)
        {
            if(a[i][j] > maxim) maxim = a[i][j];
        }
    g<<maxim;
    //printf("%d",maxim);
    return 0;
}

