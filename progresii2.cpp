#include <cstdio>

using namespace std;

FILE *fin = freopen("progresii2.in","r",stdin);
FILE *fout = freopen("progresii2.out","w",stdout);


void Run()
{
    long long int N, V, k, p;
    scanf("%lld%lld", &V, &N);

    if( N == 1 )
    {
        printf("%d\n" , V);
        return;
    }

    k = V - N + 1;
    p = k / (N - 1);

    long long int S = 0;
    S = 1ll * (k * (p + 1) - (N - 1) * p * (p + 1) / 2);

    printf("%lld\n", S);
}

int main()
{
    int T;
    scanf("%d", &T);

    for(int i = 1 ; i <= T ; ++i )
        Run();

    return 0;
}
