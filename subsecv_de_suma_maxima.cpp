#include <cstdio>
#define Nmax 100000
using namespace std;
FILE *fin = freopen("suma.in", "r", stdin);
FILE *fout = freopen("suma.out", "w", stdout);
int V[Nmax], N;


int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
    int p1 = 1 , p2 = 1, S = V[1], Smax = V[1], last = 1; // Am initializat elementele
    // In variabila last memoram indicele de unde incepe secventa curenta, atat timp cat este pozitiva.
    if( S < 0 )
    {
        S = 0;
        last = 2;
    }
    for(int i = 2 ; i <= N ; ++i )
    {
        S += V[i]; // Marim S cu numarul curent
        if( S > Smax ) // Verificam daca suma curenta, adica S, este mai mare ca Smax
        {
            Smax = S;
            p1 = last;
            p2 = i;
        }
        if( S < 0 ) // Daca S < 0 , atunci il facem 0.
        {
            S = 0;
            last = i + 1;
        }
    }
    printf("%d %d\n%d", p1, p2, Smax);
    return 0;
}
