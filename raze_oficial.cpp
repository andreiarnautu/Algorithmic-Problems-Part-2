//100P - Nicoli Marius - CN "Fratii Buzesti - Craiova"
#include <cstdio>
#include <cstring>
#define DIM 137
using namespace std;
int DI[4] = {-1,1,1,-1};
int DJ[4] = {1,-1,1,-1};

char A[DIM][DIM];

char B[DIM][DIM];

int T, N, M, i, j, max, nMax, ii, jj, d;
int main(){




	FILE *f = fopen("raze.in","r");
	FILE *g = fopen("raze.out","w");
	fscanf(f,"%d",&T);
	for (;T;T--) {
		fscanf(f,"%d %d",&N,&M);
		for (i=1;i<=N;i++)
			for (j=1;j<=M;j++)
				fscanf(f,"%d",&A[i][j]);
		memset(B,0,sizeof(B));

		for (j=1;j<=M;j++) { //liniile
			i = 1;
			for (d=0;d<=3;d++)
				for (ii = i, jj = j; ii>=0 && ii<=N && jj>=0 && jj<=M && A[ii][jj] == 0; ii+=DI[d],jj+=DJ[d])
					B[ii][jj]++;
			i = N;
			for (d=0;d<=3;d++)
				for (ii = i, jj = j; ii>=0 && ii<=N && jj>=0 && jj<=M && A[ii][jj] == 0; ii+=DI[d],jj+=DJ[d])
					B[ii][jj]++;

		}

		for (i=2;i<N;i++) { //coloanele
			j = 1;
			for (d=0;d<=3;d++)
				for (ii = i, jj = j; ii>=0 && ii<=N && jj>=0 && jj<=M && A[ii][jj] == 0; ii+=DI[d],jj+=DJ[d])
					B[ii][jj]++;
			j = M;
			for (d=0;d<=3;d++)
				for (ii = i, jj = j; ii>=0 && ii<=N && jj>=0 && jj<=M && A[ii][jj] == 0; ii+=DI[d],jj+=DJ[d])
					B[ii][jj]++;

		}

		max = 0;
		nMax = 0;
		for (i=2;i<N;i++)
			for (j=2;j<M;j++)
				if (B[i][j] > max){
					max = B[i][j];
					nMax = 1;
				} else
					if (B[i][j] == max)
						nMax++;


        fprintf(g,"%d %u\n",max,nMax);


	}

	fclose(g);

	fclose(f);
	return 0;
}
