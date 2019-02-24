#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *fin=freopen("reducere.in","r",stdin);
FILE *fout=freopen("reducere.out","w",stdout);
int n;

int main()
{
    int i,z;
    long long p=1;

    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&z);
        p=p*(z+1)%666013;
    }
    if (p==0)
        p=666012;
    else
        p--;
    printf("%d",p);
    return 0;
}
