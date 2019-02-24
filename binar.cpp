/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("binar.in", "r", stdin); FILE *fout = freopen("binar.out", "w", stdout);

static const int MAX_N = 2000 + 5;

/*-------- Data --------*/
int n, m;
char mat[MAX_N][MAX_N];

int columns[MAX_N], sorted_columns[MAX_N];
int aux[MAX_N];
/*-------- --------*/

void Sort(int line, int left, int right) {
  if(line > n || right - left <= 0) {
    std::sort(sorted_columns + left, sorted_columns + right + 1);
    return;
  }
  
  int left_index = left, right_index = right;

  while(left_index < right_index) {
    while(left_index < right_index && mat[line][sorted_columns[left_index]] == '0') {
      left_index++;
    }

    while(left_index < right_index && mat[line][sorted_columns[right_index]] == '1') {
      right_index--;
    }

    if(left_index < right_index) {
      std::swap(sorted_columns[left_index], sorted_columns[right_index]);
      left_index++; right_index--;
    }
  }

  int mid = left - 1;
  
  while(mid + 1 <= right && mat[line][sorted_columns[mid + 1]] == '0') {
    mid++;
  }

  Sort(line + 1, left, mid);
  Sort(line + 1, mid + 1, right);
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%s", mat[i] + 1);
  }

  for(int i = 1; i <= m; i++) {
    sorted_columns[i] = i;
  }

  Sort(1, 1, m);

  for(int i = 1; i <= m; i++) {
    printf("%d ", sorted_columns[i]);
  }
  printf("\n");

  return 0;
}