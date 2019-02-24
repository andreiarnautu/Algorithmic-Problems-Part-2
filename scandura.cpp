/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("scandura.in", "r", stdin);
FILE *fout = freopen("scandura.out", "w", stdout);

const int MAX_N = 1 + 1000000;

/*--------------*/
int N, M;
/*--------------*/
deque< long long > A, B;
long long SOL;
/*--------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; ++i) {
        int x; scanf("%d", &x);
        A.push_back(1LL * x);
    }
}

void Choose(const int quantity) {
    long long currentLength = 0;
    for(int i = 1; i <= quantity; i++) {
        if(!A.size()) {
            currentLength += B.front(); B.pop_front();
        } else if(!B.size()) {
            currentLength += A.front(); A.pop_front();
        } else {
            if(A.front() <= B.front()) {
                currentLength += A.front(); A.pop_front();
            } else {
                currentLength += B.front(); B.pop_front();
            }
        }
    }

    SOL += currentLength;

    if(currentLength) {
        B.push_back(currentLength);
    }

}

void Huffman() {
    int current = N;
    if(M > 2) {
        while(current % (M - 1) != 1) {
            current++; B.push_back(0);
        }
    }

    while((int)A.size() + (int)B.size() > 1) {
        Choose(M);
    }
}

void writeData() {
    printf("%lld", SOL);
}

int main() {
    readData();
    Huffman();
    writeData();
    return 0;
}
