#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    freopen("nr.in","r",stdin);
    freopen("nr.out","w",stdout);
    int n,x,i;
    scanf("%d",&n);
    vector<int>v;
   /* vector<int>v(3);
    v.push_back(10);
    printf("%d",v[3]);
    */

    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        v.push_back(x);
       // v[i]=x;

    }
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    nth_element(v.begin(),v.begin()+8,v.end());
    printf("\n");
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    return 0;
}
