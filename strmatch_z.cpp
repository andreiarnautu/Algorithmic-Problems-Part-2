/**
  *  Worg
  *  Mar 16, 2018
  *  12:13:48 AM
  */
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::ifstream fin("strmatch.in"); std::ofstream fout("strmatch.out");

const int maxLen = 2 * (2000000 + 5);
const int maxPrint = 1000;

/*-------- Data --------*/
std::string a, b, s;
int z[maxLen];
/*-------- --------*/

void Z_Algorithm() {
  z[0] = (int)s.size();
  for(int i = 1, left = 0, right = 0; i < (int)s.size(); i++) {
    if(i <= right) {
      z[i] = std::min(z[i - left], right - i + 1);
    } else {
      z[i] = 0;
    }

    while(i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }

    if(i + z[i] - 1 > right) {
      left = i; right = i + z[i] - 1;
    }
  }
}

void GetSolution() {
  int count = 0;
  std::vector<int > sol;

  int n = (int)a.size(), m = (int)b.size();

  for(int i = n; i < n + m; i++) {
    if(z[i] >= n) {
      count++;

      if((int)sol.size() < maxPrint) {
        sol.push_back(i - n);
      }
    }
  }

  fout << count << '\n';
  for(auto& itr : sol) {
    fout << itr << " ";
  }
}

int main() {
  fin >> a >> b; s = a + b;

  Z_Algorithm();

  GetSolution();

  return 0;
}
