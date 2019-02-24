/**
  *  Worg
  */
#include <cstdio>

#define inFile      "regine.in"
#define outFile     "regine.out"

using namespace std;

int n, max, l1, l2, diff, col, n1, n2;

int main() {

    freopen(inFile,"r",stdin);
    freopen(outFile,"w",stdout);

    scanf("%d ", &n);
    printf("%d\n", (2 * n + 1) / 3);

    for(int i = n; i >= 1; --i) {

        diff = (n - i) / 2;
        col = 1 + diff;

        if((col + 1) % 2 != i % 2)
            col++;
        else
            col += 2;

        n1 = diff + 1;
        n2 = (n - col) / 2 + 1;

        if(n1 + n2 == (n * 2 + 1) / 3) {

            l1 = i, l2 = col;
            break;
        }
    }

    for(int i = l1, j = 1; i <= n; i += 2, ++j)
        printf("%d %d\n", i, j);
    for(int i = l2, j = l2; i <= n; i += 2, ++j)
        printf("%d %d\n", i, j);
    return 0;
}
