/**
  *   Worg
  */
#include <cstdio>
#include <cstring>

#define DIM 100

using namespace std;
FILE *fin=freopen("zero.in","r",stdin);
FILE *fout=freopen("zero.out","w",stdout);

int L, B, P, Q;

class Huge // build a class for huge numbers, so it's easy to execute the specific operations
{
    public:
        int A[DIM];

        Huge()
        {
            memset(A, 0, sizeof(A));
        }

        inline void Set()
        {
            int aux = B - 1;
            while(aux)
                A[++A[0]] = aux % 10, aux /= 10;
        }

        inline void operator += (Huge q)
        {
            int i, t = 0;
            for(i = 1; i <= A[0] || i <= q.A[0] || t; ++i, t /= 10)
                A[i] = (t += A[i] + q.A[i]) % 10;
            A[0] = i - 1;
        }

        inline void operator *= (int nr)
        {
            int i, t = 0;
            for(i = 1; i <= A[0] || t; t /= 10, ++i)
                A[i] = (t += A[i] * nr) % 10;
            A[0] = i - 1;
        }

        inline void write()
        {
            int i;
            for(i = A[0]; i; --i)
                printf("%d", A[i]);
            printf("\n");
        }
};

Huge DP[22][22][22]; // dynamic programming

int main()
{
    scanf("%d %d %d %d", &L, &B, &P, &Q);
    DP[1][0][0].Set();

    int i, j, k, it; // DP[i][j][k] = the number of arrays with i numbers, a maximum sequence of j zeros
                     //                and the last k elements are also 0
    for(i = 2; i <= L; ++i)
        for(j = 0; j <= i; ++j)
            for(k = 0; k <= j; ++k) // there are 2 cases:
                                    //                    1) the last element is not zero
                                    //                    2) the last k elements are zero
            {
                if(k == 0) // if the last number is not zero
                {
                    if(j > i - 1)
                        continue;

                    for(it = 0; it <= j; ++it)
                        DP[i][j][k] += DP[i - 1][j][it];
                    DP[i][j][k] *= (B - 1);
                }

                else // if the last k numbers are zero
                {
                    if(j == k)
                        DP[i][j][k] += DP[i - 1][j - 1][k - 1];

                    if(i - 1 >= j)
                        DP[i][j][k] += DP[i - 1][j][k - 1];
                }

            }
    Huge sol1, sol2; // we build the two answers
    for(j = 0; j <= P; ++j)
        for(k = 0; k <= j; ++k)
            sol1 += DP[L][j][k];
    for(j = Q; j < L; ++j)
        for(k = 0; k <= j; ++k)
            sol2 += DP[L][j][k];

    sol1.write(); sol2.write();
    return 0;
}
