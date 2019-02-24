/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("strabunica.in", "r", stdin);
FILE *fout = freopen("strabunica.out", "w", stdout);

const int MAX_N = 1 + 200000;
const int bufferDim = 100000;

class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

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

int N;
int a[MAX_N];

int stackValue[MAX_N], stackPos[MAX_N];
int stackSize;

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(a[i]);
    }
}

void solveProblem() {
    long long answer = 0;
    for(int i = 1; i <= N; ++i) {
        while(a[i] < stackValue[stackSize]) {
            answer = max(answer, 1LL * stackValue[stackSize] * (i - 1 - (stackPos[stackSize - 1] + 1) + 1));
            stackSize--;
        }
        stackSize++;
        stackValue[stackSize] = a[i];
        stackPos[stackSize] = i;
    }

    for(int i = 1; i <= stackSize; ++i) {
        answer = max(answer, 1LL * stackValue[i] * (N - stackPos[i - 1]));
    }

    printf("%lld", answer);
}

int main() {
    readData();
    solveProblem();
    return 0;
}
