/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("suffixarrays.in", "r", stdin);
FILE *fout = freopen("suffixarrays.out", "w", stdout);

const int MAX_LOG = 1 + 17;
const int MAX_N = 1 + 100000 + 1;
int ZERO = 0;

/*-------- Input data --------*/
int N;
char s[MAX_N];
/*-------- Suffix array --------*/
int Index[MAX_LOG][MAX_N];
int count[MAX_N], id1[MAX_N], id2[MAX_N];
/*-------- --------*/

void readInput() {
    scanf("%s", s);
    N = strlen(s);
    s[N ++] = '$';
    s[N] = 0;
}

int& index(const int &i, const int &j) {
    if(j < MAX_N) {
        return Index[i][j];
    } else {
         return ZERO;
    }
}

void getSuffixArray() {
    /* Complexitate timp si spatiu: O(N log N), datorita Radix Sort*/
    for(int i = 0; i < N; i++) {
        count[(int)s[i]] ++;
    }
    for(int i = 0, j = 0; i < 256; i++) {
        if(count[i]) {
            /* daca avem siruri care sa inceapa cu caracterul curent */
            count[i] = j ++;
        }
    }
    for(int i = 0; i < N; i++) {
        index(0, i) = count[(int)s[i]];
    }

    for(int j = 1, L = 1; j < MAX_LOG; j++, L <<= 1) {
        /* construim id1 */
        for(int i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            count[index(j - 1, i + L)] ++;
        }
        for(int i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id1[--count[index(j - 1, i + L)]] = i;
        }

        /* construim id2 */
        for(int i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            count[index(j - 1, i)] ++;
        }
        for(int i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id2[-- count[index(j - 1, id1[i])]] = id1[i];
        }

        index(j, id2[0]) = 0;
        for(int i = 1; i < N; i++) {
            if(index(j - 1, id2[i]) == index(j - 1, id2[i - 1]) &&
                            index(j - 1, id2[i] + L) == index(j - 1, id2[i - 1] + L)) {
                index(j, id2[i]) = index(j, id2[i - 1]);
            } else {
                index(j, id2[i]) = index(j, id2[i - 1]) + 1;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        id1[index(MAX_LOG - 1, i)] = i;
    }
}

int getLCP(int a, int b) {
    int Answer = 0;
    for(int j = MAX_LOG - 1, L = (1 << (MAX_LOG - 1)); j >= 0; j--, L >>= 1) {
        if(index(j, a) == index(j, b)) {
            Answer += L;
            a += L;
            b += L;
        }
    }

    return Answer;
}

void writeOutput() {
    for(int i = 0; i < N; i++) {
        printf("%s\n", s + id1[i]);
    }
}

int main() {
    readInput();
    getSuffixArray();
    writeOutput();
    return 0;
}
