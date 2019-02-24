/*
    How about a coding trick
*/
#include <cstdio>
#define DIM 10000100
#define byte (1 << 8)
using namespace std;
FILE *fin=freopen("radixsort.in","r",stdin);
FILE *fout=freopen("radixsort.out","w",stdout);

int v[DIM], aux[DIM], pos[byte];

int main()
{
    int n, a, b, c;
    scanf("%d %d %d %d", &n, &a, &b, &c);
    v[1] = b;
    for(int i = 2; i <= n; ++i)
        v[i] = (1LL * v[i - 1] * a + b) % c;

    int bucket = 0, maxbucket = 4, val;
    for(;bucket < maxbucket; ++bucket)
    {
        for(int i = 0; i < byte; ++i)
            pos[i] = 0;
        for(int i = 1; i <= n; ++i)
        {
            val = ( v[i] >> (bucket << 3) ) & (byte - 1);
            ++pos[val];
        }
        for(int i = 1; i < byte; ++i)
            pos[i] += pos[i - 1];

        for(int i = n; i; --i)
        {
            val = ( v[i] >> (bucket << 3) ) & (byte - 1);
            aux[ pos[val]-- ] = v[i];
        }
        for(int i = n; i; --i)
            v[i] = aux[i];
    }
    for(int i = 1; i <= n; i += 10)
        printf("%d ", v[i]);
    return 0;
}
