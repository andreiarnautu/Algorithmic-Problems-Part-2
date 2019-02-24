/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("radixsort.in", "r", stdin); FILE *fout = freopen("radixsort.out", "w", stdout);

const int MAX_N = 1e7 + 5;
const int BYTE = 1 << 8;

/*-------- Data --------*/
int n, a, b, c;
int arr[MAX_N], aux[MAX_N];
int idx[BYTE];
/*-------- --------*/

void GenerateArray() {
  scanf("%d%d%d%d", &n, &a, &b, &c);

  arr[1] = b;
  for(int i = 2; i <= n; i++) {
    arr[i] = (1LL * a * arr[i - 1] + b) % c;
  }
}

void RadixSort() {
  const int bucketCount = 4;  //  Each bucket has 8 bits

  for(int bucket = 0; bucket < bucketCount; bucket++) {
    //  Reset the contors
    for(int i = 0; i < BYTE; i++) {
      idx[i] = 0;
    }

    //  Get each number's bucket corresponding to the current bit
    for(int i = 1; i <= n; i++) {
      int val = (arr[i] >> (bucket << 3)) & (BYTE - 1);
      idx[val]++;
    }

    //  Compute the contors
    for(int i = 1; i < BYTE; i++) {
      idx[i] += idx[i - 1];
    }

    //  Rearrange the numbers
    for(int i = n; i >= 1; i--) {
      int val = (arr[i] >> (bucket << 3)) & (BYTE - 1);

      aux[idx[val]] = arr[i];
      idx[val]--;
    }

    for(int i = 1; i <= n; i++) {
      arr[i] = aux[i];
    }
  }
}

int main() {
  GenerateArray();

  RadixSort();

  for(int i = 1; i <= n; i += 10) {
    printf("%d ", arr[i]);
  }

  return 0;
}
