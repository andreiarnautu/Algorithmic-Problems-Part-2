/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>

FILE *fin = freopen("strmatch.in", "r", stdin); FILE *fout = freopen("strmatch.out", "w", stdout);

const int MAX_PRINT = 1000;
const int MAX_LEN = 2e6 + 5;

/*-------- Data --------*/
char a[MAX_LEN], b[MAX_LEN];
int n, m;

int pi[MAX_LEN];

int totalOccurences;
std::vector<int > occurences;
/*-------- --------*/

void KMP() {
  pi[1] = 0;

  for(int i = 2, k = 0; i <= n; i++) {
    while(k > 0 && a[i] != a[k + 1]) {
      k = pi[k];
    }

    if(a[i] == a[k + 1]) {
      k++;
    }
    pi[i] = k;
  }



  for(int i = 1, k = 0; i <= m; i++) {
    while(k > 0 && b[i] != a[k + 1]) {
      k = pi[k];
    }

    if(b[i] == a[k + 1]) {
      k++;
    }

    if(k == n) {
      totalOccurences++; k = pi[k];
      if((int)occurences.size() < MAX_PRINT) {
        occurences.push_back(i - n);
      }
    }
  }

  printf("%d\n", totalOccurences);
  for(auto& itr : occurences) {
    printf("%d ", itr);
  }
}

int main() {
  scanf("%s%s", a + 1, b + 1);
  n = strlen(a + 1); m = strlen(b + 1);

  KMP();
  return 0;
}
