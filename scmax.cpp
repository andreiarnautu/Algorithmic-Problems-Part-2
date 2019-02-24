//Subsir crescator maximal O(N log N)
#include <cstdio>
#define INF 2000000009
#define DIM 100003
using namespace std;

FILE *fin=freopen("scmax.in","r",stdin);
FILE *fout=freopen("scmax.out","w",stdout);

int V[DIM], P[DIM], Q[DIM], S[DIM];
int n, len;

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n ; ++i)
        scanf("%d", &V[i]);
}

int Insert(int k, int left, int right)
{
    int mid;

    mid = (left + right) / 2;
    if(left == right)
    {
        if(right > len)
            Q[++len + 1] = INF;
        Q[right] = k;
        return right;
    }
    if(k <= Q[mid])
        return Insert(k, left, mid);
    return Insert(k, mid + 1, right);
}

void BuildPQ()
{
    int i;
    Q[1] = INF;

    for(i = 1; i <= n ; ++i)
        P[i] = Insert(V[i], 1, len + 1);
}

void BuildS()
{
    int i, k = n;

    for(i = len; i > 0 ; --i)
    {
        while( P[k] != i )
            --k;
        S[i] = V[k];
    }
}

void Write()
{
    printf("%d\n", len);
    for(int i = 1; i <= len ; ++i)
        printf("%d ", S[i]);
}

int main()
{
    Read();
    BuildPQ();
    BuildS();
    Write();
}
