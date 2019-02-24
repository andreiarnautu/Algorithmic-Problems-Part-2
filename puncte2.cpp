#include <cstdio>
using namespace std;
FILE *fin=freopen("puncte2.in","r",stdin);
FILE *fout=freopen("puncte2.out","w",stdout);
unsigned long long int N , V[20];

int main()
{
    scanf("%d", &N);
    V[1] = 1;
    for(int i = 2 ; i <= N ; ++i)
    {
        V[i] = 2 * V[i - 1];
        for(int j = 1 ; j < i - 1 ; ++j )
            V[i] += V[j] * V[i - j - 1];
    }
    printf("%d", V[N]);
}
