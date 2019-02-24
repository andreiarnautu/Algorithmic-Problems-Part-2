/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("rsp.in", "r", stdin);
FILE *fout = freopen("rsp.out", "w", stdout);

const int MAX_LEN = 1 + 1000000;
const int MAX_INF = 0x3fffffff;

/*-------- Structures --------*/
struct DP {
    int dp[2][2];
};
/*-------- Input data --------*/
int test_count;
char text[MAX_LEN];
/*-------- Algorithm data --------*/
char *s;
DP mvc[MAX_LEN];
int crt_index;
/*-------- --------*/

int eval();
int factor();
int term();

int eval() {  //  Conectare in serie
    int index = (++ crt_index);
    DP current, next;

    int a = factor();
    current = mvc[a];
    while(*s == 'S') {
        s ++;
        int b = factor();

        //  Trebuie sa legam in serie {current} cu {b}
        for(int i = 0; i <= 1; i++) {
            for(int j = 0; j <= 1; j++) {
                next.dp[i][j] = std::min(current.dp[i][0] + mvc[b].dp[0][j], current.dp[i][1] + mvc[b].dp[1][j] - 1);
            }
        }

        current = next;
    }

    mvc[index] = current;

    return index;  //  Returnam index-ul nodului de dinamica
}

int factor() {  //  Conectare in paralel
    int index = (++ crt_index);
    DP current, next;

    int a = term();
    current = mvc[a];
    while(*s == 'P') {
        s ++;
        int b = term();

        //  Trebuie sa legam in paralel {current} cu {b}
        for(int i = 0; i <= 1; i++) {
            for(int j = 0; j <= 1; j++) {
                next.dp[i][j] = std::min(MAX_INF,
                                         current.dp[i][j] + mvc[b].dp[i][j] - (i + j));
            }
        }
        current = next;
    }
    mvc[index] = current;

    return index;  //  Returnam indexul nodului de dinamica
}

int term() {  //  Termen
    int index = (++ crt_index);

    if(*s == '(') {  //  Avem o expresie in paranteza
        s ++;
        mvc[index] = mvc[eval()];
        s ++;
    } else {  //  Avem o retea de baza
        mvc[index].dp[0][0] = MAX_INF;
        mvc[index].dp[0][1] = 1;
        mvc[index].dp[1][0] = 1;
        mvc[index].dp[1][1] = 2;
        s ++;
    }

    return index;  //  Returnam index-ul nodului de dinamica
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count --) {
        scanf("%s", text);
        s = text; crt_index = 0;

        int root = eval();
        printf("%d\n", std::min(std::min(mvc[root].dp[0][0], mvc[root].dp[1][1]),
                                std::min(mvc[root].dp[0][1], mvc[root].dp[1][0])));
    }

    return 0;
}
