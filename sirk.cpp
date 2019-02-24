/**
  *  Worg
  */
#include <iostream>

using namespace std;

int main() {
    //  Observam ca sirul este format din sirurile (1) (2 1 2) (3 2 1 2 3) (4 3 2 1 2 3 4) puse unul dupa altul
    //  Observam imediat ca lungimea unui sir care incepe cu valoarea i (din cele de mai sus) are 2*i - 1 elemente
    int K;
    cin >> K;

    int i = 1;
    while(2 * i - 1 < K) {
        K -= (2 * i - 1);
        i ++;
    }
    //  Stim acum ca elementul nostru se gaseste pe pozitia K in sirul (i i-1 i-2 ... 2 1 2 ... i-2 i-1 i)
    if(K > (i - 1)) {
        K -= (i - 1);
        cout << K;
    } else {
        for(int j = i; j > 1; j--) {
            K--;
            if(K == 0) {
                cout << j;
                break;
            }
        }
    }

    return 0;
}
