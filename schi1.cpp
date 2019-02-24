#include <cstdio>
#include <cassert>
#define MAXN 100010
#include <cstring>
using namespace std;

int N, M, K, c, i, j, v, Q, x, p;
struct punct{int p, t;};

int A[MAXN];
punct C[MAXN];


int cb(int x){
int st, dr, m, poz;
    st=1; dr=v; poz=0;
    while (st<=dr && poz==0)   {
        m=(st+dr)/2;
        if(C[m].p==x) poz=m;
        else
          if (C[m].p>x) dr=m-1; else st=m+1;
    }
        return poz;
}

int main()
{
    freopen("schi1.in","r",stdin);
    freopen("schi1.out","w",stdout);
    scanf("%d\n",&N);
    assert(N>=1 && N<=100000);
    C[0].p=-1; v=0;
    for(i=1; i<=N; i++){
            scanf("%d",&A[i]);
            assert(A[i]>=0 && A[i]<=1000000000);
            if(C[v].p>=A[i]) C[v].t++;
            else {
                C[++v].p=A[i]; C[v].t=1;
            }
    }
    scanf("%d\n",&Q);
    assert(Q>=1 && Q<=100000 );
    for(i=1; i<=Q; i++){
            scanf("%d",&x);
            assert(x>=0 && x<=1000000000);
            p=cb(x);
            if (p==0)printf("0 " );
            else printf("%d ", C[p].t);
    }
    printf("\n");
    return 0;
}
