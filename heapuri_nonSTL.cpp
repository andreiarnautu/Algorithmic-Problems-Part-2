/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("heapuri.in", "r", stdin); FILE *fout = freopen("heapuri.out", "w", stdout);

const int MAX_N = 2e5 + 5;

//-------- Data --------
struct Node {
  int value, order;

  Node() {}
};

int n, size, cursor;
int where[MAX_N];
Node heap[MAX_N];
//-------- --------

void Insert() {
  cursor++; size++;
  scanf("%d", &heap[size].value); heap[size].order = cursor;
  where[cursor] = size;

  int i = size;
  while (i > 1 && heap[i].value < heap[i >> 1].value) {
    std::swap(heap[i], heap[i >> 1]);

    where[heap[i].order] = i; where[heap[i >> 1].order] = i >> 1;
    i >>= 1;
  }
}

void Erase() {
  int x; scanf("%d", &x); x = where[x];

  std::swap(heap[x], heap[size]); where[heap[x].order] = x; size--;

  if(!size) return;

  while (x * 2 <= size) {
    if (x * 2 + 1 > size || heap[x * 2].value < heap[x * 2 + 1].value) {
      if (heap[x].value <= heap[x * 2].value) break;

      std::swap(heap[x], heap[x * 2]);
      where[heap[x].order] = x; where[heap[x * 2].order] = x * 2;

      x = x * 2;
    } else {
      if (heap[x].value <= heap[x * 2 + 1].value) break;

      std::swap(heap[x], heap[x * 2 + 1]);
      where[heap[x].order] = x; where[heap[x * 2 + 1].order] = x * 2 + 1;

      x = x * 2 + 1;
    }
  }

  while (x > 1 && heap[x].value < heap[x >> 1].value) {
    std::swap(heap[x], heap[x >> 1]);

    where[heap[x].order] = x; where[heap[x >> 1].order] = x >> 1;
    x >>= 1;
  }
}

int main() {
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    int type; scanf("%d", &type);

    if (type == 1) {
      Insert();
    } else if (type == 2) {
      Erase();
    } else {
      printf("%d\n", heap[1].value);
    }
  }

  return 0;
}