/**
  *  Worg
  *  Aflam cate numere sunt divizibile cu x.
  *  Parcurgem numerele si ne uitam cati divizori primi are numarul curent.
  *  Daca are numar impar, atunci adunam count[i] * (count[i] - 1) / 2 la suma. Altfel scadem.
  */
#include <cstdio>

FILE *fin = freopen("pairs.in", "r", stdin); FILE *fout = freopen("pairs.out", "w", stdout);

const int MAX_VALUE = 1e6 + 5;

/*-------- Data --------*/
int n;
bool exists[MAX_VALUE];
int divisor_number[MAX_VALUE];
bool is_redundant[MAX_VALUE];
/*-------- --------*/

void ReadAndCompute() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int x; scanf("%d", &x);
    exists[x] = true;
  }
}

void ComputeDivisorNumbers() {
  for (int i = 2; i < MAX_VALUE; i++) {
    if (divisor_number[i] == 0) {
      for (int j = i; j < MAX_VALUE; j += i) {
        divisor_number[j]++;
      }
    }
  }

  for (int i = 2; i * i < MAX_VALUE; i++) {
    for (int j = i * i; j < MAX_VALUE; j += i * i) {
      is_redundant[j] = true;
    }
  }
}

long long ComputeSolution() {
  long long solution = 1LL * n * (n - 1) / 2;

  for (int i = 2; i < MAX_VALUE; i++) {
    if (is_redundant[i]) continue;

    int count_divisible = 0;

    for (int j = i; j < MAX_VALUE; j += i) {
      count_divisible += exists[j];
    }

    if (divisor_number[i] & 1) {
      solution -= 1LL * count_divisible * (count_divisible - 1) / 2;
    } else {
      solution += 1LL * count_divisible * (count_divisible - 1) / 2;
    }
  }

  return solution;
}


int main() {
  ReadAndCompute();

  ComputeDivisorNumbers();

  printf("%lld\n", ComputeSolution());

  return 0;
}
