#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("reuniune.in","r",stdin);
FILE *fout=freopen("reuniune.out","w",stdout);

struct dreptunghi{long long int x1, x2, y1, y2;};

dreptunghi A, B, C, D, E, F, G;

void Read()
{
    scanf("%lld %lld %lld %lld", &A.x1, &A.y1, &A.x2, &A.y2);
    scanf("%lld %lld %lld %lld", &B.x1, &B.y1, &B.x2, &B.y2);
    scanf("%lld %lld %lld %lld", &C.x1, &C.y1, &C.x2, &C.y2);
}

void Make_Rectangle(dreptunghi M, dreptunghi N, dreptunghi &P)
{
    P.x1 = max(M.x1, N.x1);
    P.y1 = max(M.y1, N.y1);
    P.x2 = min(M.x2, N.x2);
    P.y2 = min(M.y2, N.y2);

    if( P.x1 > P.x2 || P.y1 > P.y2 )
    {
        P.x1 = P.x2;
        P.y1 = P.y2;
    }
}

long long int Area(dreptunghi O)
{
    return 1LL * (O.x2 - O.x1) * (O.y2 - O.y1);
}

long long int Perimeter(dreptunghi O)
{
    return 1LL * 2 * (O.x2 - O.x1 + O.y2 - O.y1);
}

void Solve()
{
    Make_Rectangle(A, B, D);
    Make_Rectangle(A, C, E);
    Make_Rectangle(B, C, F);
    Make_Rectangle(D, C, G);

    long long int Ar, P;

    Ar = Area(A) + Area(B) + Area(C) - Area(D) - Area(E) - Area(F) + Area(G);
    P = Perimeter(A) + Perimeter(B) + Perimeter(C) - Perimeter(D) - Perimeter(E) - Perimeter(F) + Perimeter(G);

    printf("%lld %lld", Ar, P);
}

int main()
{
    Read();
    Solve();
}
