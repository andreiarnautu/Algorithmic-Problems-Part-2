// Sortare...cu STL(aparent foarte eficienta)
#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("algsort.in","r",stdin);
FILE *fout=freopen("algsort.out","w",stdout);

int N, V[500013];


int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);

    sort( V + 1 , V + N + 1 );

    for(int i = 1 ; i <= N ; ++i )
        printf("%d ", V[i]);

    return 0;
}
