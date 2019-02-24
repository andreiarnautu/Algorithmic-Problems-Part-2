/**
  *  Worg
  */
#include <vector>
#include <fstream>

std::ifstream fin("algsort.in"); std::ofstream fout("algsort.out");

const unsigned int MAX_INF = 1U << 31;
const unsigned int MAX_N = 500000 + 5;

unsigned int seg_tree[MAX_N * 4];

void UpdateNode(int node, int left, int right) {
  int left_son = node << 1, right_son = left_son + 1;

  seg_tree[node] = std::min(seg_tree[left_son], seg_tree[right_son]);
}

void Update(int node, int left, int right, int index, int value) {
  if (left == right) {
    seg_tree[node] = value; return;
  }

  int mid = (left + right) >> 1;
  int left_son = node << 1, right_son = left_son + 1;

  if (index <= mid) {
    Update(left_son, left, mid, index, value);
  } else {
    Update(right_son, mid + 1, right, index, value);
  }

  UpdateNode(node, left, right);
}

void Extract(int node, int left, int right) {
  if (left == right) {
    fout << seg_tree[node] << " ";
    seg_tree[node] = MAX_INF;
    return;
  }

  int mid = (left + right) >> 1;
  int left_son = (node << 1), right_son = left_son + 1;

  if (seg_tree[left_son] < seg_tree[right_son]) {
    Extract(left_son, left, mid);
  } else {
    Extract(right_son, mid + 1, right);
  }

  UpdateNode(node, left, right);
}

int main() {
  int n; fin >> n;

  for (int i = 1; i <= n; i++) {
    int value; fin >> value;
    Update(1, 1, n, i, value);
  }

  for (int i = 1; i <= n; i++) {
    Extract(1, 1, n);
  }
  printf("\n");
  return 0;
}