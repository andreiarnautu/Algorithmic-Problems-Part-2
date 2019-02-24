/**
  *  Worg
  */
#include <stack>
#include <vector>
#include <algorithm>
 
#include <fstream>
#ifdef LOCAL
std::ifstream cin("f.in");
std::ofstream cout("f.out");
#else
std::ifstream cin("unter.in");
std::ofstream cout("unter.out");
#endif // LOCAL
 
using namespace std;
 
const int MAX_N = 3e5 + 5;
 
/*-------- Data --------*/
int n, d;
long long average[MAX_N];
 
long long power;
/*-------- --------*/
 
void ReadData() {
    cin >> n >> d;
 
    power = 1;
    for(int i = 1; i <= d; i++) {
        power *= 10;
    }
 
    for(int i = 1; i <= n; i++) {
        double x; cin >> x;
        x *= power; x += 0.1;
        average[i] = x;
    }
}
 
void Solve() {
    int ans = true;
    long long mins = 0, maxs = 0;
 
    for(int i = 1; i <= n; i++) {
        mins += power;
        maxs += 5 * power;
 
        long long first_good = average[i] * i;
        long long last_good = 1LL * (average[i] + 1) * i - 1;
 
        if(first_good % power) {
            first_good -= first_good % power;
            first_good += power;
        }
        last_good -= last_good % power;

        if(first_good > last_good) {
            ans = false; break;
        }
        if(maxs < first_good || last_good < mins) {
            ans = false; break;
        } else {
            mins = std::max(mins, first_good);
            maxs = std::min(maxs, last_good);
        }

    }
 
    if(ans) {
        cout << "DA\n";
    } else {
        cout << "NU\n";
    }
}
 
int main() {
    int test_count; cin >> test_count;
 
    for(int i = 0; i < test_count; i++) {
        ReadData();
        Solve();
    }
 
    return 0;
}