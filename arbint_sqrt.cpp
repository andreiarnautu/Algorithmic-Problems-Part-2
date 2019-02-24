/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("arbint.in", "r", stdin); FILE *fout = freopen("arbint.out", "w", stdout);

const int MAX_N = 1e5 + 5;
const int BUCKET_SIZE = 300;

/*-------- Data --------*/
int n, m;
int v[MAX_N];
int bucket_max[MAX_N / BUCKET_SIZE + 10];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  for(int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }
}

void Initialize() {
  for(int i = 0; i < n; i++) {
    if(i % BUCKET_SIZE == 0) {
      bucket_max[i / BUCKET_SIZE] = v[i];
    } else {
      bucket_max[i / BUCKET_SIZE] = std::max(bucket_max[i / BUCKET_SIZE], v[i]);
    }
  }
}

void Update(int position, int value) {
  int bucket = position / BUCKET_SIZE;

  v[position] = value;

  bucket_max[bucket] = 0;
  for(int i = BUCKET_SIZE * bucket; i < BUCKET_SIZE * (bucket + 1); i++) {
    bucket_max[bucket] = std::max(bucket_max[bucket], v[i]);
  }
}

int Query(int left, int right) {
  int bucket_left = left / BUCKET_SIZE;
  int bucket_right = right / BUCKET_SIZE;

  int answer = 0;

  for(int i = left; i < BUCKET_SIZE * (bucket_left + 1) && i <= right; i++) {
    answer = std::max(answer, v[i]);
  }
  for(int i = std::max(BUCKET_SIZE * bucket_right, left); i <= right; i++) {
    answer = std::max(answer, v[i]);
  }
  for(int i = bucket_left + 1; i < bucket_right; i++) {
    answer = std::max(answer, bucket_max[i]);
  }

  return answer;
}

void ProcessOperations() {
  for(int i = 0; i < m; i++) {
    int type, a, b; scanf("%d%d%d", &type, &a, &b);

    if(type == 0) {
      a--; b--;
      printf("%d\n", Query(a, b));
    } else {
      a--;
      Update(a, b);
    }
  }
}

int main() {
  ReadInput();

  Initialize();

  ProcessOperations();

  return 0;
}