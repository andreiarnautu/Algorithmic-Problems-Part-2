/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("bleach.in"); std::ofstream fout("bleach.out");

void Sort(std::vector<int > &v, const int &n, const int &k) {
  std::priority_queue<int, std::vector<int > , std::greater<int> > heap;

  for (int i = 0; i < std::min(n, k + 1); i++) {
    heap.push(v[i]);
  }

  for (int i = 0; i < n; i++) {
    v[i] = heap.top(); heap.pop();

    if (i + k + 1 < n) {
      heap.push(v[i + k + 1]);
    }
  }
}

long long GetInitialPower(const std::vector<int > &v, const int &n) {
  long long initial_power = 0;
  long long sum = 0;

  for (auto& x : v) {
    if (sum < x) {
      initial_power += (x - sum);
      sum += (x - sum);
    }

    sum += x;
  }

  return initial_power;
}

int main() {
  int n, k; fin >> n >> k;

  std::vector<int > v(n);
  for (auto& x : v) {
    fin >> x;
  }

  Sort(v, n, k);

  fout << GetInitialPower(v, n);

  return 0;
}