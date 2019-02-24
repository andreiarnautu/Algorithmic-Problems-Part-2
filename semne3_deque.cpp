// Deque
#include <cstdio>
#include <deque>
#define Nmax 500010
using namespace std;
FILE *fin=freopen("semne3.in","r",stdin);
FILE *fout=freopen("semne3.out","w",stdout);
deque <int> A;
int N, Nr, i;
char S[Nmax];

void Preprocess()
{
    for(int i = 1 ; i <= N ; ++i )
        A.push_back( i );
}

int main()
{
    scanf("%d", &N);
    Preprocess();
    getchar();
    gets(S);
    while( i < N - 1 )
    {
        Nr = 1;
        while( S[i + 1] == S[i] && i < N - 1 )
        {
            ++i;
            ++Nr;
        }
        if( S[i] == '>' )
        {
            for(int j = Nr ; j > 0 ; --j )
                printf("%d ",A[j]);
            A.erase(A.begin() + 1, A.begin() + Nr + 1);
        }
        if( S[i] == '<' )
        {
            for(int j = 0 ; j < Nr ; ++j )
                printf("%d ", A[j]);
            A.erase(A.begin(), A.begin() + Nr);
        }
        ++i;
    }
    printf("%d", A[0]);
    return 0;
}
