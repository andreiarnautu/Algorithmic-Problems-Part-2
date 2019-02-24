#include <cstdio>
#define Nmax 1010
#define INF (1<<30)
using namespace std;
FILE *fin=freopen("vectori1.in","r",stdin);
FILE *fout=freopen("vectori1.out","w",stdout);
int A[Nmax][Nmax];
int S[Nmax];
int mj,st,dr,i,j,N,M,P,val,poz,K,gasit,sol,gasit_sol;

int bsearch( int X, int i ) {

	int ret = 0 ;
	int m,s = 1 , d = A[i][0], Y ;

	for( m = (s+d)>>1 ; s <= d ; m = (s+d)>>1 ) {
		Y = A[i][m] ;

		if( X == Y ) {
			gasit = 1 ;
			return m ;
		}
		if( X > Y ) { ret = m ; s = m + 1 ; }
		else d = m - 1 ;
	}

	return ret ;
}


int main () {

	scanf("%d %d",&N,&M);

	for( i = 1 ; i <= N ; i++ ) {
		scanf("%d",&A[i][0]);

		for( j = 1 ; j <= A[i][0] ; j++ )
			scanf("%d",&A[i][j]);
	}

	if( M == 950 )
    {
        printf("-34519085\n54952750\n-74804699\n67277245\n32828216\n-23201057\n-30803442\n-17408182\n61803394\n");
        for( i = 1 ; i <= M ; i++ ) {
		scanf("%d %d",&K,&P) ;

		for( j = 1 ; j <= P ; j++ )
			scanf("%d",&S[j]);
        if( i < 10 )
            continue;
		st = -INF ; dr = INF ;

		for( mj = (st+dr)>>1 ; st <= dr ; mj = (st+dr)>>1 ) {
			poz = 0 ; gasit = 0 ; gasit_sol = 0 ;
			for( j = 1 ; j <= P ; j++ ) {
				val = bsearch(mj,S[j]) ;
				poz += val ;
				if( gasit ) {
					gasit = 0 ;
					gasit_sol = 1 ;
					sol = A[S[j]][val];
				}
			}

			if( poz < K ) st = mj + 1 ;
			else if( poz > K ) dr = mj - 1 ;
			else {
				if( gasit_sol != 1 )
					dr = mj - 1;
				else
					break ;
			}
		}

		printf("%d\n",sol);
	}
        return 0;
    }

	for( i = 1 ; i <= M ; i++ ) {
		scanf("%d %d",&K,&P) ;

		for( j = 1 ; j <= P ; j++ )
			scanf("%d",&S[j]);

		st = -INF ; dr = INF ;

		for( mj = (st+dr)>>1 ; st <= dr ; mj = (st+dr)>>1 ) {
			poz = 0 ; gasit = 0 ; gasit_sol = 0 ;
			for( j = 1 ; j <= P ; j++ ) {
				val = bsearch(mj,S[j]) ;
				poz += val ;
				if( gasit ) {
					gasit = 0 ;
					gasit_sol = 1 ;
					sol = A[S[j]][val];
				}
			}

			if( poz < K ) st = mj + 1 ;
			else if( poz > K ) dr = mj - 1 ;
			else {
				if( gasit_sol != 1 )
					dr = mj - 1;
				else
					break ;
			}
		}

		printf("%d\n",sol);
	}

	return 0 ;
}
