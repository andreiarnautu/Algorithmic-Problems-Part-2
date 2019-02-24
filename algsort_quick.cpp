/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

FILE *fin = freopen("algsort.in", "r", stdin); FILE *fout = freopen("algsort.out", "w", stdout);

const int MAX_N = 5e5 + 5;

//-------- Data --------
int n;
int arr[MAX_N];
//-------- --------

void ReadInput() {
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  std::random_shuffle(arr, arr + n);
}

void QuickSort(int begin, int end) {
  if (end - begin <= 1) return;

  int left = begin, right = end - 1, pivot = arr[begin + ((end - begin) >> 1)];

  do {
    while (left < end - 1 && arr[left] < pivot) {
      left++;
    }

    while (right > begin && arr[right] > pivot) {
      right--;
    }

    if (left <= right) {
      std::swap(arr[left], arr[right]);
      left++; right--;
    }
  } while (left <= right);

  QuickSort(begin, right + 1);
  QuickSort(left, end);
}

void PrintOutput() {
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

int main() {
  ReadInput();

  srand((unsigned)time(NULL));
  QuickSort(0, n);

  PrintOutput();

  return 0;
}