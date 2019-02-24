/**
  *  Worg
  *
  *  prefix[i][j] = 1, daca putem potrivi s[1..i] cu c[1..j]
  *                 0, altfel
  *  suffix[i][j] = 1, daca putem potrivi s[i..n] cu c[j..m]
  *                 0, altfel
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_L       1 + 1500 + 10

using namespace std;
FILE *fin=freopen("sablon3.in","r",stdin);
FILE *fout=freopen("sablon3.out","w",stdout);

char s[MAX_L], c[MAX_L];
bool prefix[MAX_L][MAX_L], suffix[MAX_L][MAX_L], ok[MAX_L][MAX_L];
int t, n, m;

void getPrefix() {

    memset(ok, 0, sizeof(ok));
    prefix[0][0] = 1;
    for(int i = 0; i <= m; ++i)
        ok[0][i] = 1;

    for(int i = 1; i <= n && s[i] == '*'; ++i)
        prefix[i][0] = 1,
        ok[i][0] = 1;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {

            if(s[i] == '*')
                prefix[i][j] = ok[i - 1][j];
            else if(s[i] == '?' || s[i] == c[j])
                prefix[i][j] = prefix[i - 1][j - 1];
            else
                prefix[i][j] = 0;

            ok[i][j] = ok[i][j - 1] || prefix[i][j];
        }
}

void getSuffix() {

    memset(ok, 0, sizeof(ok));

    suffix[n + 1][m + 1] = 1;
    for(int i = m + 1; i; --i)
        ok[n + 1][i] = 1;

    for(int i = n; i && s[i] == '*'; --i)
        suffix[i][m + 1] = 1,
        ok[i][m + 1] = 1;

    for(int i = n; i; --i)
        for(int j = m; j; --j) {

            if(s[i] == '*')
                suffix[i][j] = ok[i + 1][j];
            else if(s[i] == '?' || s[i] == c[j])
                suffix[i][j] = suffix[i + 1][j + 1];
            else
                suffix[i][j] = 0;

            ok[i][j] = ok[i][j + 1] || suffix[i][j];
        }
}

void solveTest() {

    gets(c + 1);
    m = strlen(c + 1);
    memset(suffix, 0, sizeof(suffix));
    memset(prefix, 0, sizeof(prefix));

    /*for(int i = 0; i <= 1510; ++i)
        for(int j = 0; j <= 1510; ++j)
            prefix[i][j] = suffix[i][j] = 0;*/

    getPrefix();
    getSuffix();
   /* for(int i = 0; i <= m; ++i) {

        for(int j = 0; j <= n; ++j)
            printf("%d ", prefix[i][j]);
        printf("\n");
    }
    printf("-------------------------\n"); */

    bool sol = suffix[1][1];
    for(int i = 1; i <= n; ++i)
        if('a' <= s[i] && s[i] <= 'z')
            for(int j = 0; j <= m; ++j)
                if(prefix[i - 1][j] && suffix[i + 1][j + 1])
                    sol = 1;

    printf("%d\n", sol);
}

int main() {

    gets(s + 1);
    n = strlen(s + 1);
    scanf("%d ", &t);
    for(; t; --t)
        solveTest();
    return 0;
}
