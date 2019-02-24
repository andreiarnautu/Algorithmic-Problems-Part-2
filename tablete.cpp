#include <fstream>
#include <iostream>
 
using namespace std;
 
ifstream fin ("tablete.in");
ofstream fout ("tablete.out");
 
int n, k, i, j, x, r;
 
int main (){
    fin >> n >> k;
    if (k % 2 == 0) {
        x = 1;
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                fout << x++ << ' ';
            }
            fout << "\n";
        }
        return 0;
    }
    x = 1;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (j == 1 && r != 0) {
                fout << r << ' ';
                r = 0;
                continue;
            } else {
                if (i == n - 1 && j == n) {
                    fout << n * n;
                } else {
                    if (j == k) {
                        if (x % 2 == 0) {
                            fout << x << ' ';
                        } else { 
                            fout << x + 1 << ' ';
                            r = x++;
                        }
                    } else {
                        fout << x << ' ';
                    }
                    x++;
                }
            }
        }
        fout << "\n";
    }
}