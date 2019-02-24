/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int n;
std::vector<std::pair<char, int > > ops;

int a, b, c;

int main() {
  scanf("%d ", &n); ops.resize(n);
  for(auto& itr : ops) {
    scanf("%c %d ", &itr.first, &itr.second);
  }

  b = (1 << 10) - 1;

  for(int bit = 0, x, y; bit < 10; bit++) {
    x = 0; y = 1 << bit;

    for(auto& itr : ops) {
      int here = (1 << bit) & itr.second;

      if(itr.first == '^') {
        x ^= here; y ^= here;
      } else if(itr.first == '|') {
        x |= here; y |= here;
      } else {
        x &= here; y &= here;
      }
    }

    if(x == 0 && y != 0) {
      continue;
    } else if(x != 0 && y == 0) {
      a ^= (1 << bit);
    } else if(x == 0 && y == 0) {
      b ^= (1 << bit);
    } else if(x != 0 && y != 0) {
      c ^= (1 << bit);
    }
  }

  printf("3\n^ %d\n& %d\n| %d\n", a, b, c);
	return 0;
}
