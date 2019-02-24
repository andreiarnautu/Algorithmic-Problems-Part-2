/**
  *  Worg
  */
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <algorithm>

FILE *fin = freopen("sdo.in", "r", stdin); FILE *fout = freopen("sdo.out", "w", stdout);

const int kBufferSize = 1e5;

class InputReader {

public:
  char buffer[kBufferSize];
  int cursor;

  void getBuffer() {
    cursor = 0; fread(buffer, 1, kBufferSize, stdin);
  }

  InputReader() {
    getBuffer();
  }

  bool digit(char c) {
    return '0' <= c && c <= '9';
  }

  InputReader& operator >>(int &number) {
    char sgn = '+';

    while(!digit(buffer[cursor])) {
      sgn = buffer[cursor];
      if(++cursor == kBufferSize) {
        getBuffer();
      }
    }

    number = 0;
    while(digit(buffer[cursor])) {
      number = number * 10 + buffer[cursor] - '0';
      if(++cursor == kBufferSize) {
        getBuffer();
      }
    }
    number = (sgn == '-') ? -number : number;
    return *this;
  }
} cin;

int KthElement(std::vector<int > &v, int left, int right, int k) {
  assert(left <= right);

  int all_equal = true;
  for (int i = left + 1; i <= right; i++) {
    if (v[i] != v[i - 1]) {
      all_equal = false; break;
    }
  }

  if (all_equal) {
    return v[left];
  }

  int pivot = v[left + rand() % (right - left + 1)];
  int a = left, b = right;

  while (a < b) {
    while (a < b && v[a] < pivot) {
      a++;
    }

    while (a < b && v[b] > pivot) {
      b--;
    }

    if (a < b) {
      std::swap(v[a], v[b]);

      a++; b--;
    }
  }

  int count_lower = 0;
  for (int i = left; i <= right && v[i] <= pivot; i++) {
    count_lower++;
  }

  if (k <= count_lower) {
    return KthElement(v, left, left + count_lower - 1, k);
  } else {
    return KthElement(v, left + count_lower, right, k - count_lower);
  }
}

int main() {
  int n, k;
  std::vector<int > v;

  cin >> n >> k;
  v.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  printf("%d\n", KthElement(v, 0, n - 1, k));
  return 0;
}