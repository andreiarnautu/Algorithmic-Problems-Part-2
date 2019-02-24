#include <cstdio>
using namespace std;
FILE *fin = freopen("set.in", "r", stdin);
FILE *fout = freopen("set.out" , "w", stdout);
long long K, V[100], k;
int main()
{
    scanf("%lld", &K);
    k = K;
    K *= (K - 1);
    printf("%lld\n", K);
    while( K )
    {
        ++V[0];
        V[V[0]] = K % 10;
        K /= 10;
    }
    int i , t = 0;
    for( i = 1 ; i <= V[0] || t ; ++i , t /= 10 )
        V[i] = ( t += V[i] * (k + 1) ) % 10;
    V[0] = i - 1;
    for( i = V[0] ; i > 0 ; --i )
        printf("%d",V[i]);
}
