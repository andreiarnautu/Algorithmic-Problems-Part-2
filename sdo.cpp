// How about a coding trick?
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *fin=freopen("sdo.in","r",stdin);
FILE *fout=freopen("sdo.out","w",stdout);

vector <int> V;

int main()
{
    int n, x, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        V.push_back(x);
    }
    nth_element(V.begin(), V.begin() + k - 1, V.end());
    printf("%d", V[k - 1]);
    return 0;
}
