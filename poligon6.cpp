// How about a coding trick?
#include <cstdio>
#include <algorithm>
#include <ctime>
#define DIM 1010
using namespace std;
FILE *fin=freopen("poligon6.in","r",stdin);
FILE *fout=freopen("poligon6.out","w",stdout);

int n;
int R[DIM], nr[200200], dif, act;
int cnt;
double V[200200];

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &R[i]);
}

inline void Gen(int val)
{
    int i, j;
    for(i = 1; i < val; ++i)
        {
            j = sqrt((double)val * val - i * i);
            if( i * i + j * j == val * val && j > 0 )
            {
                V[++cnt] = (double) i / j;
                //printf("%d %d ", i, j);
            }
        }
}

int main()
{
    clock_t start, finish;
    start = clock();
    Read();
    for(int i = 1; i <= n; ++i)
        Gen( R[i] );
    printf("%d\n", cnt);
    sort( V + 1, V + cnt + 1 );

    dif = 0, act = 1;
    for(int i = 1; i <= cnt; ++i)
    {
        if( V[i] != V[i + 1] )
        {
            nr[++dif] = act;
            act = 1;
        }
        else
            ++act;
    }
    printf("%d\n", dif);
    for(int i = 1; i <= dif; ++i)
        printf("%d ", nr[i]);
    finish = clock();
    //printf("\n%.5f", (float) (finish - start) / CLOCKS_PER_SEC);
    return 0;
}
