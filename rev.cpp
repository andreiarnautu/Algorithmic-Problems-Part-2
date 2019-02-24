/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

FILE *fin = freopen("rev.in", "r", stdin); FILE *fout = freopen("rev.out", "w", stdout);

const int kDim = 1e5 + 5;
const int kMagic = 800;

/*-------- Data --------*/
struct Seg {
  int left, right, rev;

  Seg() {}

  Seg(int _left, int _right, int _rev) {left = _left; right = _right; rev = _rev;}
};

int n, m;
int vec[kDim], aux[kDim];

Seg segs[kMagic + 5];
int cnt;
/*-------- --------*/

void Initialize() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    vec[i] = i;
  }

  segs[cnt = 1] = {1, n, 0};
}

void Reset() {
  int cursor = 0;

  for(int i = 1; i <= cnt; i++) {
    if(segs[i].rev == 0) {
      for(int j = segs[i].left; j <= segs[i].right; j++) {
        cursor++; aux[cursor] = vec[j];
      }
    } else {
      for(int j = segs[i].right; j >= segs[i].left; j--) {
        cursor++; aux[cursor] = vec[j];
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    vec[i] = aux[i];
  }

  segs[cnt = 1] = {1, n, 0};
}

void Split(int idx, int k) {  //  Keep k here and put the others in the next one
  cnt++;
  for(int i = cnt; i > idx; i--) {
    segs[i] = segs[i - 1];
  }

  if(segs[idx].rev == 0) {
    segs[idx].right = segs[idx].left + k - 1; segs[idx + 1].left = segs[idx].right + 1;
  } else {
    segs[idx].left = segs[idx].right - k + 1; segs[idx + 1].right = segs[idx].left - 1;
  }
}

void Print(int idx, int k) {
  if(segs[idx].rev == 0) {
    printf("%d\n", vec[segs[idx].left + k - 1]);
  } else {
    printf("%d\n", vec[segs[idx].right - k + 1]);
  }
}

void ProcessOperations() {
  for(int i = 1; i <= m; i++) {
    //  If there are too many blocks, reset everything
    if(cnt >= kMagic) {
      Reset();
    }

    //  Update the blocks
    int x, y; scanf("%d%d", &x, &y);
    for(int j = 1, rest = x - 1; j <= cnt && rest > 0; j++) {
      if(segs[j].right - segs[j].left + 1 <= rest) {
        rest -= (segs[j].right - segs[j].left + 1);
      } else {
        Split(j, rest); break;
      }
    }

    for(int j = 1, rest = y; j <= cnt && rest > 0; j++) {
      if(segs[j].right - segs[j].left + 1 <= rest) {
        rest -= (segs[j].right - segs[j].left + 1);
      } else {
        Split(j, rest); break;
      }
    }

    int id1 = 1, id2 = 1;
    for(int j = 1, rest = x; j <= cnt; j++) {
      if(segs[j].right - segs[j].left + 1 < rest) {
        rest -= (segs[j].right - segs[j].left + 1);
      } else {
        id1 = j; break;
      }
    }

    for(int j = 1, rest = y; j <= cnt; j++) {
      if(segs[j].right - segs[j].left + 1 < rest) {
        rest -= (segs[j].right - segs[j].left + 1);
      } else {
        id2 = j; break;
      }
    }

    assert(id1 <= id2);

    for(int j1 = id1, j2 = id2; j1 <= j2; j1++, j2--) {
      std::swap(segs[j1], segs[j2]);
      segs[j1].rev ^= 1;

      if(j1 != j2) {
        segs[j2].rev ^= 1;
      }
    }

    //  Print kth position
    int k; scanf("%d", &k);
    for(int j = 1; j <= cnt; j++) {
      if(segs[j].right - segs[j].left + 1 < k) {
        k -= segs[j].right - segs[j].left + 1;
      } else {
        Print(j, k); break;
      }
    }
  }
}

int main() {
  Initialize();

  ProcessOperations();
  return 0;
}
