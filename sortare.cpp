/**
  *  Worg
  */
#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>
FILE *fin = freopen("sortare.in", "r", stdin); FILE *fout = freopen("sortare.out", "w", stdout);

const int MAX_N = 5000 + 5;

//-------- Data --------
int n;
std::vector<int > pivots[MAX_N];
int a[MAX_N], b[MAX_N], c[MAX_N];

int ans[MAX_N];
int h;
//-------- --------

void ReadInput() {
  scanf("%d", &n);

  for (int i = 2; i <= n; i++) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    pivots[i] = {a, b, c};

    std::sort(pivots[i].begin(), pivots[i].end());
  }
}

void Place(int position, int value) {
  int index = 0;
  while (position > 0) {
    index++;

    if (ans[index] == 0) {
      position--;
    }
  }

  ans[index] = value;
}

void Solve(int size) {
  if(size <= 0) {
    return;
  }

  h++;
  if (size == 1) {
    Place(1, 1); return;
  }

  if (pivots[size][0] != pivots[size][1] && pivots[size][1] != pivots[size][2]) {  ///  Case 1 : they are all distinct
    Place(pivots[size][2], size);
    Place(pivots[size][1], size - 1);

    Solve(size - 2);
  } else {  ///  Case 2 : we have at least two equal elements
    Place(pivots[size][1], size);
    Solve(size - 1);
  }
}

void PrintOutput() {
  printf("%d\n", h);

  for (int i = 1; i <= n; i++) {
    assert(1 <= ans[i] && ans[i] <= n);
    for (int j = 1; j < i; j++) {
      assert(ans[i] != ans[j]);
    }
  }

  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
}

int main() {
  ReadInput();

  Solve(n);

  PrintOutput();
  return 0;
}