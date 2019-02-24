#include <fstream>
using namespace std;
ifstream in("sir8.in");
ofstream out("sir8.out");
int N;
int V1[17002], V2[17002];
void Solve()
{
    int pos = 1, k = 1, nr, j;
    while( pos <= V1[0] )
    {
    //    printf("*");
        nr = 1;
        j = pos + 1;
        while( V1[j] == V1[pos] && j <= V1[0] )
        {
            ++j;
            ++nr;
        }
        V2[k] = nr;
        V2[k+1] = V1[pos];
        k += 2;
        //if( nr == 1 )
        pos = j;
    }
    V1[0] = k - 1;

    for(int i=1 ; i<= V1[0] ; ++i)
    {
        V1[i] = V2[i];
       // out<<V1[i];
    }
   // out<<'\n';
}
int main()
{
    in>>N;
    V1[0] = 1;
    V1[1] = 1;
    for(int i=1 ; i<N ; ++i)
        Solve();
    for(int i=1; i<=V1[0] ; ++i)
        out<<V1[i];
    return 0;
}
