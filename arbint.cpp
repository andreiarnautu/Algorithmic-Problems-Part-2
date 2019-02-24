/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define mid ((left + right) / 2)
#define leftSon (node * 2)
#define rightSon (node * 2 + 1)

FILE *fin = freopen("arbint.in", "r", stdin); FILE *fout = freopen("arbint.out", "w", stdout);

const int MAX_N = 1e5 + 5;

/*-------- Data --------*/
int n, m;
int aint[MAX_N * 4];
/*-------- --------*/

void Update(int node, int left, int right, int pos, int value) {
  if(left == right) {
    aint[node] = value; return;
  }

  if(pos <= mid) {
    Update(leftSon, left, mid, pos, value);
  } else {
    Update(rightSon, mid + 1, right, pos, value);
  }

  aint[node] = std::max(aint[leftSon], aint[rightSon]);
}

void Query(int node, int left, int right, int first, int last, int &queryAnswer) {
  if(first <= left && right <= last) {
    queryAnswer = std::max(queryAnswer, aint[node]); return;
  }

  if(first <= mid) {
    Query(leftSon, left, mid, first, last, queryAnswer);
  }
  if(mid < last) {
    Query(rightSon, mid + 1, right, first, last, queryAnswer);
  }
}

int main() {
  scanf("%d%d", &n, &m);

  //  Initialize the segment tree
  for(int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);
    Update(1, 1, n, i, x);
  }

  //  Process operations
  for(int i = 1; i <= m; i++) {
    int type, a, b; scanf("%d%d%d", &type, &a, &b);

    if(type == 0) {
      int queryAnswer = 0; Query(1, 1, n, a, b, queryAnswer);
      printf("%d\n", queryAnswer);
    } else {
      Update(1, 1, n, a, b);
    }
  }

  return 0;
}
