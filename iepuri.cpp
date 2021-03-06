/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstdlib>

FILE *fin = freopen("iepuri.in", "r", stdin); FILE *fout = freopen("iepuri.out", "w", stdout);

const int mod = 666013;

namespace Matrix {
  class Matrix {
  private:
    std::vector<std::vector<int > > a;
    
  public:
    int n, m;
    
    Matrix(): n(0), m(0) {}

    Matrix(const int _n, const int _m) : n(_n), m(_m), a(std::vector<std::vector<int > >(_n + 1, std::vector<int >(_m + 1, 0))) {}

    std::vector<int >& operator [] (const int i) {
      return a[i];
    }
  };

  Matrix Multiply (Matrix &_m1, Matrix &_m2) {
    if(_m1.m != _m2.n) {
      printf("Error: can't multiply"); exit(0);
    }
    
    int n = _m1.n, m = _m1.m, p = _m2.m;

    Matrix ret(n, p);

    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= p; j++) {
        for(int k = 1; k <= m; k++) {
          ret[i][j] = (ret[i][j] + 1LL * _m1[i][k] * _m2[k][j] % mod) % mod;
        }
      }
    }

    return ret;
  }

  Matrix Power(Matrix &_m, const int exp) {
    int n = _m.n;
    Matrix ans(n, n); ans[1][1] = 1; ans[2][2] = 1;
    Matrix aux(n, n); aux = _m;

    for(long long i = 1; i <= exp; i <<= 1) {
      if(i & exp) {
        ans = Multiply(ans, aux);
      }
      aux = Multiply(aux, aux);
    }

    return ans;
  }
}

int main() {
  int test_count; scanf("%d", &test_count);

  for(int i = 0; i < test_count; i++) {
    int x, y, z, a, b, c, n; scanf("%d%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c, &n);

    Matrix::Matrix p(3, 1); p[1][1] = x; p[2][1] = y; p[3][1] = z;
    Matrix::Matrix q(3, 3); q[1][2] = 1; q[2][3] = 1; q[3][1] = c; q[3][2] = b; q[3][3] = a;
    q = Power(q, n - 1);

    Matrix::Matrix ans = Multiply(q, p);
    printf("%d\n", ans[1][1]);
  }

  return 0;
}