#include <cstdio>
#define Mod 19573
using namespace std;
FILE *fin=freopen("sortari.in","r",stdin);
FILE *fout=freopen("sortari.out","w",stdout);

int N;
int A[203];

void Solve()
{
    int Sol, Plus;
    for(int i = 4 ; i <= N ; ++i )
    {
        Sol = 0;
        Plus = 0;
        for(int j = 1; j < i ; ++j )
            for(int k = j + 1 ; k <= i ; ++k)
            {
                Plus = ( A[j - 1] * A[k - j - 1] ) % Mod;
                Plus = ( Plus * A[i - k] ) % Mod;
                Sol = ( Sol + Plus ) % Mod;
            }
        A[i] = ( 2 * Sol ) % Mod;
    }
    printf("%d", A[N]);
}

int main()
{
    scanf("%d", &N);
    A[0] = 1, A[1] = 1, A[2] = 2, A[3] = 6;
    Solve();
}
