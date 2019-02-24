#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define DIM 1500000

int nrprime, K;
bitset <DIM> CE;

void Ciur() {
    CE[0] = CE[1] = 1;

    for(long long i = 2; i <= DIM; ++i) {
        if(CE[i] == 0) {
            ++nrprime;

            if(nrprime == K + 1) {
                cout << i * i << '\n';
                return ;
            }

            for(long long j = i * i; j < DIM; j += i) {
                CE[j] = 1;
            }
        }
    }
}

int main() {
    freopen("prim.in","r",stdin);
    freopen("prim.out","w",stdout);

    scanf("%d\n", &K);

    Ciur();

    return 0;
}
