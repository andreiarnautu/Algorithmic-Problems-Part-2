/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("xor.in", "r", stdin);
FILE *fout = freopen("xor.out", "w", stdout);

const int bufferDim = 100000;

class inputReader {
private:
        char buffer[bufferDim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

int P;

int getCnt(int A, int B, int bit) {
    /* cate numere de la A la B contin bitul bit in reprezentarea binara */
    int answer = 0;

    int nxtBit = bit + 1;
    int pos1 = (A / (1 << nxtBit)) * (1 << nxtBit) + (1 << bit);
    int pos2 = (B / (1 << nxtBit)) * (1 << nxtBit) + (1 << bit);
    if(pos2 > B) {
        pos2 -= (1 << nxtBit);
    }

    if(pos2 < pos1 || pos1 > B) {
        return answer;
    } else {
        if(pos1 < pos2) {
            answer = ((pos2 - pos1 - 1) / (1 << nxtBit)) * (1 << bit);
            if(pos1 < A) {
                answer += (1 << bit) - (A - pos1);
            } else {
                answer += (1 << bit);
            }
            answer += min((1 << bit), B - pos2 + 1);
        } else {
            if(pos1 < A) {
                answer = (1 << bit) - (A - pos1);
                if(pos1 + (1 << bit) - 1 > B) {
                    answer -= (pos1 + (1 << bit) - B - 1);
                }
            } else {
                answer = min(1 << bit, B - pos1 + 1);
            }
        }
        return answer;
    }
}

void solveQuery() {
    long long answer = 0;
    int L1, C1, L2, C2;
    cin.getInt(L1); cin.getInt(C1); cin.getInt(L2); cin.getInt(C2);

    for(int bit = 0; 1 << bit <= max(L2, C2); bit++) {
        /* vrem sa vedem in reprezentarea binara a cate linii si coloane sa gaseste bitul curent */
        int x = getCnt(L1, L2, bit);
        int y = getCnt(C1, C2, bit);
        int partial1 = 1LL * (1LL * x * (C2 - C1 + 1)) % P;
        int partial2 = 1LL * (1LL * y * (L2 - L1 + 1)) % P;
        int partial3 = 1LL * (2LL * x * y) % P;
        int partial4 = partial1 + partial2 - partial3;
        if(partial4 < P) {
            partial4 += P;
        }
        partial4 %= P;
        partial4 = (1LL * partial4 * (1LL << bit)) % P;
        answer = (answer + 1LL * partial4) % P;
    }
    printf("%lld\n", answer);
}

int main() {
    int T;
    cin.getBuffer(); cin.getInt(T); cin.getInt(P);
    for(; T; --T) {
        solveQuery();
    }
    return 0;
}
