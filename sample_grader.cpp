#include <stdio.h>

void initialize(long long n, long long m);
void update(long long x, long long y1, long long y2);
int query(long long x, long long y);

int main() {
  long long n, m, x, y1, y2;
  int op;

  FILE *fin = fopen("matrix.in", "r");
  FILE *fout = fopen("matrix.out", "w");
  fscanf(fin, "%lld%lld", &n, &m);

  initialize(n, m);

  while (fscanf(fin, "%d%lld%lld", &op, &x, &y1) == 3) {
    if (op == 0) {
      /* update */
      fscanf(fin, "%lld", &y2);
      update(x, y1, y2);
    } else {
      /* query */
      fprintf(fout, "%d\n", query(x, y1));
    }
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
