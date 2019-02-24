#include <cstdio>
using namespace std;
FILE *fin=freopen("pseudobil.in","r",stdin);
FILE *fout=freopen("pseudobil.out","w",stdout);
int N, K, D;
bool A[3003][3003];
int B[3003][3003];
void Solve1()
{
    int x;
    x= D/2 - 1;
    printf("%d",2*x*x+D-1);
}
void Solve2()
{
    int M,x,y;
    scanf("%d",&M);
    for(int i=1; i<N*2 ; ++i)
        for(int j=1; j<N*2 ; ++j)
            B[i][j]= B[i-1][j] + B[i][j-1] - B[i-1][j-1] + A[i][j];
    while(M--)
    {
        scanf("%d%d",&x,&y);
        int x1,y1;
        x1=x+y-1;
        y1=N-x+y;
        printf("%d\n",B[x1+D][y1] - B[x1+D][y1-D-1] - B[x1-1][y1] + B[x1-1][y1-D-1]);
    }
}
void Read()
{
    int x,a,b;
    scanf("%d%d%d%d",&x,&N,&K,&D);
    for(int i=0; i<K ; ++i)
        scanf("%d%d",&a,&b) , A[a+b-1][N-a+b]=1;
    if(x==1)
        Solve1();
    else
        Solve2();
}
int main()
{
    Read();
    return 0;
}
