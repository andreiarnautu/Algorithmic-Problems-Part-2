/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

const int MAX_N = 1e5 + 5;
const int mod = 10007;
const int BLOCK_SIZE = 300;

int block_min[MAX_N / BLOCK_SIZE + 10];
int n;
int v[MAX_N];

void Sort() {
  //  Initialize the minimum value for each block
  for(int i = 0; i < n; i++) {
    if(i % BLOCK_SIZE == 0) {
      block_min[i / BLOCK_SIZE] = i;
    } else if(v[i] < v[block_min[i / BLOCK_SIZE]]) {
      block_min[i / BLOCK_SIZE] = i;
    }
  }

  for(int i = 0; i < n; i++) {
    //  Search the value which will be on the ith position in the sorted array
    int index = i, current_block = i / BLOCK_SIZE;

    //  Brute force the current block in O(BLOCK_SIZE)
    for(int j = i; j < BLOCK_SIZE * (current_block + 1) && j < n; j++) {
      if(v[j] < v[index]) {
        index = j;
      }
    }

    //  For the following blocks, look only at the block's minimum element
    for(int block = current_block + 1; block * BLOCK_SIZE < n; block++) {
      if(v[block_min[block]] < v[index]) {
        index = block_min[block];
      }
    }

    std::swap(v[i], v[index]);

    //  Update the changed block
    if(index >= BLOCK_SIZE * (current_block + 1)) {
      int block = index / BLOCK_SIZE;

      block_min[block] = block * BLOCK_SIZE;
      for(int i = block * BLOCK_SIZE + 1; i < n && i < (block + 1) * BLOCK_SIZE; i++) {
        if(v[i] < v[block_min[block]]) {
          block_min[block] = i;
        }
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  Sort();

  long long ans = 0;
  for(int i = 0, j = n - 1; i < n; i++, j--) {
    ans += 1LL * v[i] * v[j];
    ans %= mod;
  }

  printf("%lld\n", ans);

  return 0;
}