/**
  *  Worg
  */
#include <cmath>
#include <iostream>

using namespace std;

int main() {

    long long int k;
    cin >> k;
    for(int a = 1; a * a <= k / 2; ++a) {

        int b = k - a * a;
        int radical = sqrt(double(b));

        if(radical * radical == b)
            cout << a << " " << radical << '\n';
    }
    return 0;
}
