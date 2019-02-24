#include <fstream>
using namespace std;
ifstream in("premii.in");
ofstream out("premii.out");
int n,k,j,m[200][200],nr=1;
int main()
{
    int i;
    in>>n>>k;
    if(n/k % 2 ==1)
    {
        out<<"0";
        return 0;
    }
    else
    {
        for(j=1;j<=n/k;j++)
        {
            if(j%2==1)
                for(i=1;i<=k;i++)
                {
                    m[i][j]=nr;
                    ++nr;
                }
            else
                for(i=k;i>=1;i--)
                {
                    m[i][j]=nr;
                    ++nr;
                }
        }
        for(i=1;i<=k;i++)
        {
            for(j=1;j<=n/k;j++)
                out<<m[i][j]<<" ";
            out<<'\n';
        }
    }
}
