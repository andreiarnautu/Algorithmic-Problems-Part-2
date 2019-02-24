/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("cautbin.in", "r", stdin); FILE *fout = freopen("cautbin.out", "w", stdout);

const int MAX_N = 1e5 + 5;

/*-------- Data --------*/
int n, m;
int v[MAX_N];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
}

int SearchLower(const int &value) {
  int left = 1, right = n, answer = 0;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(v[mid] <= value) {
      answer = mid; left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return answer;
}

int SearchUpper(const int &value) {
  int left = 1, right = n, answer = 0;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(v[mid] >= value) {
      answer = mid; right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return answer;
}

void ProcessQueries() {
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int type, x; scanf("%d%d", &type, &x);

    if(type == 0) {
      int position = SearchLower(x);

      if(position == -1 || v[position] != x) {
        printf("-1\n");
      } else {
        printf("%d\n", position);
      }
    } else if(type == 1) {
      int position = SearchLower(x);

      printf("%d\n", position);
    } else {
      int position = SearchUpper(x);

      printf("%d\n", position);
    }
  }
}

int main() {
  ReadInput();

  ProcessQueries();
  return 0;
}
