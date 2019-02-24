#include <fstream>
using namespace std;
ifstream in("submdisj.in");
ofstream out("submdisj.out");
int m[201][100];

int main()
{
    int n,i,j,k=1;
    in>>n;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            m[i][j]=k;
            k++;
        }
    k=1;
    for(i=n;i<2*n-1;i++)
        for(j=0;j<n;j++)
        {
            m[i][j]=k;
            ++k;
        }
    for(i=0;i<n;i++)
    {
        k=0;
        for(j=i;j<i+n;j++)
        {
            out<<m[j][k]<<" ";
            ++k;
        }
        out<<endl;
    }
    return 0;
}
