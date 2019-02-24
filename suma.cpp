#include <fstream>

using namespace std;

ifstream fin("suma.in"); ofstream fout("suma.out");

int n, q;
int v[100003], s[100003];

int main() 
{
  fin >> n;
  for(int i = 1; i <= n; i++) 
  {
    fin >> v[i];
  }

  for(int i = 1; i <= n; i++) 
  {
    s[i] = s[i - 1] + v[i];                             
  }

  fin >> q;
  for(int i = 1; i <= q; i++) 
  {
    int x, y;
    fin >> x >> y;

    fout << s[y] - s[x - 1] << '\n';
  }

  return 0;
}
