/**
  *  Worg
  */
#include <iostream>
#include <algorithm>

using namespace std;
//ifstream cin("main.in");
//ofstream cout("main.out");

const int MAX_N = 1 + 100;

int N;
int A[MAX_N], B[MAX_N];

void ReadInput() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for(int i = 0; i < N; i++) {
        cin >> B[i];
    }
}

void CheckIfProportional() {
    bool proportional = true;

    for(int i = 0; i < N - 1; i++) {
        if(A[i] * B[i] != A[i + 1] * B[i + 1]) {
            proportional = false;
        }
    }

    if(proportional) {
        cout << "DA";
    } else {
        cout << "NU";
    }
}

int comp(int a, int b) {
    return (a > b);
}

int main() {
    ReadInput();
    sort(A, A + N);
    sort(B, B + N, comp);
    CheckIfProportional();
    return 0;
}
