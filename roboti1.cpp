// Implementare Simoiu Robert - 100 pct. Traducere Pascal -> C++
#include <cstdio>

const char FIN[] = "roboti1.in";
const char FOU[] = "roboti1.out";
const int MAX = 55;

int m, n, nr, l, c;
int x[MAX], y[MAX], tr[MAX][MAX];
char ori[MAX], depl[MAX][MAX];
bool exista[MAX];

void date()
{
    int i;

    scanf("%d %d\n", &l, &c);
    scanf("%d\n", &n);
    nr = n;
    for (i = 1; i <= n; i++)
    {
        scanf("%d %d %c\n", &x[i], &y[i], &ori[i]);
        tr[x[i]][y[i]] = 1;
        exista[i] = 1;
    }
    scanf("%d\n", &m);
    for (i = 1; i <= n; i++)
        fgets(depl[i] + 1, MAX , stdin);
}

void miscare_l(char c, char *c_nou)
{
    switch ( c )
    {
    case 'E' :
        *c_nou = 'N';
        break ;
    case 'V' :
        *c_nou = 'S';
        break ;
    case 'S' :
        *c_nou = 'E';
        break ;
    case 'N' :
        *c_nou = 'V';
        break ;
    }
}

void miscare_r(char c, char *c_nou)
{
    switch ( c )
    {
    case 'E' :
        *c_nou = 'S';
        break ;
    case 'V' :
        *c_nou = 'N';
        break ;
    case 'S' :
        *c_nou = 'V';
        break ;
    case 'N' :
        *c_nou = 'E';
        break ;
    }
}

void miscare_f(int l, int c, char ch, int *l_nou, int *c_nou)
{
    switch ( ch )
    {
    case 'E' :
        *c_nou = c + 1;
        break ;
    case 'V' :
        *c_nou = c - 1;
        break ;
    case 'S' :
        *l_nou = l + 1;
        break ;
    case 'N' :
        *l_nou = l - 1;
        break ;
    }
}

void deplasare()
{
    int i, j, vechil, vechic;
    short a[MAX][MAX], b[MAX][MAX], p, q;

    for (i = 1; i <= m; i++)
    {
        for (p = 1; p <= l; p++)
            for (q = 1; q <= c; q++)
                a[p][q] = 0;
        for (j = 1; j <= nr; j++)
            if ( exista[j] )
                if ( depl[j][i] == 'L' || depl[j][i] == 'R')
                     a[x[j]][y[j]] = 1, b[x[j]][y[j]] = j;
        for (j = 1; j <= nr; j++)
            if ( exista[j] )
            {
                switch ( depl[j][i] )
                {
                   case 'L' : miscare_l(ori[j], &ori[j]); break ;
                   case 'R' : miscare_r(ori[j], &ori[j]); break ;
                   case 'F' :
                   {
                       miscare_f(x[j], y[j], ori[j], &x[j], &y[j]);
                       if (x[j] == 0 || y[j] == 0 || x[j] > l || y[j] > c)
                           exista[j] = 0;
                       else
                       {
                           tr[x[j]][y[j]]++;
                           if (a[x[j]][y[j]] == 0)
                                a[x[j]][y[j]] = 1, b[x[j]][y[j]] = j;
                           else  exista[j] = 0, exista[b[x[j]][y[j]]] = 0;
                       }
                       break;
                   }
                }
            }
    }
    n = 0;
    for (i = 1; i <= nr; i++)
        if ( exista[i] ) ++n;
}
void afisare()
{
    int i, j, max, p, q;

    printf("%d\n", n);
    max = tr[1][1];
    p = q = 1;
    for (i = 1; i <= l; i++)
        for (j = 1; j <= c; j++)
            if (tr[i][j] > max)
                max = tr[i][j], p = i, q = j;
    printf("%d %d %d", p, q, max);
}

int main()
{
    freopen(FIN,"r",stdin);
    freopen(FOU,"w",stdout);

    date(), deplasare(), afisare();

    return 0;
}
