/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("xcmmdc.in", "r", stdin);
FILE *fout = freopen("xcmmdc.out", "w", stdout);

const int MAX_N = 1 + 1002 + 1;
const int MAX_P2 = 10;
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

/*--------------------*/
int M, N, K, Q;
int mat[MAX_N][MAX_N];
/*--------------------*/
int gcd[MAX_N][MAX_N][MAX_P2];
/*--------------------*/
int Solution[MAX_N];

void readInput() {
    cin.getBuffer();
    cin.getInt(M); cin.getInt(N); cin.getInt(K); cin.getInt(Q);
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            cin.getInt(mat[i][j]);
        }
    }
}

int getGcd(int a, int b) {
    int r;
    while(b) {
        r = a % b; a = b; b = r;
    }
    return a;
}


void computeGCD() {
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            gcd[i][j][0] = mat[i][j];
        }
    }

    for(int k = 1; (1 << k) <= min(N, M); k++) {
        const int step = (1 << (k - 1));
        for(int i = 1; i + step <= M; i++) {
            for(int j = 1; j + step <= N; j++) {
                gcd[i][j][k] = getGcd(gcd[i][j][k - 1], getGcd(gcd[i + step][j][k - 1],
                                                               getGcd(gcd[i][j + step][k - 1], gcd[i + step][j + step][k - 1])));
            }
        }
    }
}

int getCrtGcd(int x, int y, int L) {
    int pow = 0;
    while(1 << (pow + 1) <= L) {
        pow++;
    }
    int step = (1 << pow);

    return getGcd(gcd[x][y][pow], getGcd(gcd[x + L - step][y][pow],
                                         getGcd(gcd[x][y + L - step][pow], gcd[x + L - step][y + L - step][pow])));
}

int lowerBound(int x, int y) {
    int left = 1, right = min(M - x + 1, N - y + 1), Answer = 1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        int crtGcd = getCrtGcd(x, y, mid);

        if(crtGcd <= K) {
            Answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return Answer;
}

int upperBound(int x, int y) {
    int left = 1, right = min(M - x + 1, N - y + 1), Answer = right;

    while(left <= right) {
        int mid = (left + right) >> 1;
        int crtGcd = getCrtGcd(x, y, mid);

        if(crtGcd >= K) {
            Answer = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return Answer;
}

void checkPos(int x, int y) {
    int indexA = lowerBound(x, y);
    int indexB = upperBound(x, y);

    int gcdA = getCrtGcd(x, y, indexA);
    int gcdB = getCrtGcd(x, y, indexB);

   // printf("%d %d %d %d\n", x, y, indexA, indexB);

    if(gcdA != K || gcdB != K) {
        return;
    }

    Solution[indexA]++;
    Solution[indexB + 1]--;
}

void writeOutput() {
    for(int i = 1; i <= min(N, M); i++) {
        Solution[i] = Solution[i - 1] + Solution[i];
    }

    for(int i = 1; i <= Q; i++) {
        int L; cin.getInt(L);
        printf("%d\n", Solution[L]);
    }
}

int main() {
    readInput();
    computeGCD();
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            checkPos(i, j);
        }
    }
    writeOutput();

    return 0;
}
