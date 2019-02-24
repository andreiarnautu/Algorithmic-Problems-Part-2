/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("sortare2.in", "r", stdin);
FILE *fout = freopen("sortare2.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*-------- Data --------*/
int N;
int where[MAX_N];
/*-------- --------*/

int main() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int x; scanf("%d", &x);
        where[x] = i;
    }

    int solution = 0;
    for(int i = 2; i <= N; i++) {
        if(where[i] < where[i - 1]) {
            solution ++;
        }
    }
    printf("%d\n", solution);

    return 0;
}
