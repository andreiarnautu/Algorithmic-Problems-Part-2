/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("disjoint.in", "r", stdin); FILE *fout = freopen("disjoint.out", "w", stdout);

const int MAX_N = 1e5 + 5;

/*-------- Data --------*/
int n, m;
int father[MAX_N];
/*-------- --------*/

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

int blocksRemained;

void Unite(int x, int y) {
  x = Group(x); y = Group(y);

  father[x] = y;
}

int main() {
  scanf("%d%d", &n, &m);

  //  Initialize sets
  for(int i = 1; i <= n; i++) {
    father[i] = i;
  }

  //  Process operations
  for(int i = 1; i <= m; i++) {
    int type, x, y; scanf("%d%d%d", &type, &x, &y);

    if(type == 1) {
      Unite(x, y);
    } else {
      if(Group(x) == Group(y)) {
        printf("DA\n");
      } else {
        printf("NU\n");
      }
    }
  }
  return 0;
}