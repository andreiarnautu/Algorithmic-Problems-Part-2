/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

FILE *fin = freopen("password1.in", "r", stdin); FILE *fout = freopen("password1.out", "w", stdout);

const int MAX_A = 3e7 + 5;
const int MAX_B = 3e6 + 5;
const int sigma = 26;

//---------------- Data ----------------//
char a[MAX_A], b[MAX_B];
int n, m;


int a_freq[sigma], b_freq[sigma];
int size;
char sol[MAX_B];
//---------------- ----------------//

void ReadData() {
  scanf("%s%s", a, b);
  n = strlen(a); m = strlen(b);

  for (int i = 0; i < n; i++) {
    a_freq[a[i] - 'a']++;
  }
  for (int i = 0; i < m; i++) {
    b_freq[b[i] - 'a']++;
  }
}

char* GetSolution() {
  //  Check if the solution exists
  for (int i = 0; i < sigma; i++) {
    if (b_freq[i] > a_freq[i]) {
      strcpy(sol, "impossible");
      return sol;
    }
  }

  for (int i = 0; i < n; i++) {
    int character = a[i] - 'a';

    a_freq[character]--;
    if (b_freq[character] <= 0) continue;

    while (size > 0 && character < sol[size - 1] && a_freq[sol[size - 1]] >= b_freq[sol[size - 1]] + 1) {
      size--;
      b_freq[sol[size]]++;
    }

    b_freq[character]--;
    sol[size] = character;
    size++;
  }

  for (int i = 0; i < size; i++) {
    sol[i] += 'a';
  }

  return sol;
}

int main() {
  ReadData();

  printf("%s\n", GetSolution());

  return 0;
}