/**
  *  Worg
  */
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
//ifstream fin("main.in");
//ofstream fout("main.out");

const int MAX_N = 1 + 30000 + 2;

/*-------- Input data --------*/
int N, A;
int x, y;
int power, orientation;
/*-------- Finding solution --------*/
vector< int > Set[MAX_N];
/*-------- --------*/

void processData() {
    if(orientation == 0) {
        for(int line = x, range = power; line < min(x + power, N + 1); line++, range--) {
            Set[line].push_back(y + 1);
            Set[line].push_back(max(1, y - range + 1));
        }
    } else if(orientation == 1) {
        for(int line = x, range = power; line < min(x + power, N + 1); line++, range--) {
            Set[line].push_back(y);
            Set[line].push_back(min(N + 1, y + range));
        }
    } else if(orientation == 2) {
        for(int line = x, range = power; line > max(x - power, -1); line--, range--) {
            Set[line].push_back(y);
            Set[line].push_back(min(N + 1, y + range));
        }
    } else {
        for(int line = x, range = power; line > max(x - power, -1); line--, range--) {
            Set[line].push_back(y + 1);
            Set[line].push_back(max(1, y - range + 1));
        }
    }
}

void readInput() {
    cin >> A;

    for(int i = 1; i <= A; i++) {
        cin >> x >> y >> power >> orientation;
        x ++; y ++;
       // fout << x << " " << y << " " << power << " " << orientation << '\n';
       if(orientation == 0) {
            y --;
       } else if(orientation == 2) {
            x --;
       } else if(orientation == 3) {
            x --; y --;
       }
        processData();
    }
}

int getSolution() {
    int Solution = 0;

    for(int line = 1; line <= N + 1; line++) {
        if(Set[line].empty()) {
            continue;
        } else {
            sort(Set[line].begin(), Set[line].end());
        }

        int crt = 0;
        bool state = 0;
        for(int i = 0; i < (int)Set[line].size() - 1; i++) {
            state ^= 1;
            if(state == 1) {
                Solution += Set[line][i + 1] - Set[line][i];
                crt += Set[line][i + 1] - Set[line][i];
            }
        }

        Set[line].clear();

    /*    if(crt > 0) {
            printf("Line %d: %d\n", line, crt);
        }*/
    }

    return Solution;
}

int main() {
    while(cin >> N) {
        readInput();
        cout << getSolution() << '\n';
    }
    return 0;
}
