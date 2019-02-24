#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("suffixarrays.in", "r", stdin);
FILE *fout = freopen("suffixarrays.out", "w", stdout);

const int MAX_LGN = 17;
const int MAX_N = 100000;

int Index[1 + MAX_LGN][MAX_N + 1];
int ZERO = 0;


int& index(const int &i, const int &j) {
  if (j < MAX_N + 1)
    return Index[i][j];
  else
    return ZERO;
}


int count[MAX_N + 1];
int id1[MAX_N + 1];
int id2[MAX_N + 1];

int LCP[MAX_N + 1];


int lcp(int a, int b) {
    int answer = 0;
    for(int j = MAX_LGN, L = (1 << MAX_LGN); j >= 0; j--, L /= 2) {
        if (index(j, a) == index(j, b)) {
            answer += L;
            a += L;
            b += L;
        }
    }
    return answer;
}


int main() {
    char *s = new char[MAX_N + 1 + 1];
    scanf("%s", s);
    int N = strlen(s);
    s[N] = '$';
    N++;
    s[N] = 0;

    int i, j;
    for(i = 0; i < N; i++) {
        count[(unsigned int)s[i]]++;
    }

    for(i = 0, j = 0; i < 256; i++) {
        if (count[i]) {
            count[i] = j++;
        }
    }
    for(i = 0; i < N; i++) {
        index(0, i) = count[(unsigned int)s[i]];
    }

    int L;
    for(j = 1, L = 1; j <= MAX_LGN; j++, L *= 2) {
        for(i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(i = 0; i < N; i++) {
            count[index(j - 1, i + L)]++;
        }
        for(i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(i = N - 1; i >= 0; i--) {
            id1[--count[index(j - 1, i + L)]] = i;
        }

        for(i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(i = 0; i < N; i++) {
            count[index(j - 1, i)]++;
        }
        for(i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(i = N - 1; i >= 0; i--) {
            id2[--count[index(j - 1, id1[i])]] = id1[i];
        }

        index(j, id2[0]) = 0;
        for(i = 1; i < N; i++) {
            if (index(j - 1, id2[i]) == index(j - 1, id2[i - 1])
                            && index(j - 1, id2[i] + L) == index(j - 1, id2[i - 1] + L)) {
                index(j, id2[i]) = index(j, id2[i - 1]);
            } else {
                index(j, id2[i]) = index(j, id2[i - 1]) + 1;
            }
        }
    }

    for(i = 0; i < N; i++) {
        id1[index(MAX_LGN, i)] = i;
    }

    for(i = 0; i < N; i++) {
        printf("%s\n", s + id1[i]);
    }

   /* for(i = 1; i < N; i++) {
        LCP[i] = lcp(id1[i], id1[i - 1]);
    }

    for(i = 0; i < N; i++) {
        printf("%d %s\n", LCP[i], s + id1[i]);
    }*/

  return 0;
}
