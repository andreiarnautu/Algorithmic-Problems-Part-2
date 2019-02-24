/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("sms.in", "r", stdin);
FILE *fout = freopen("sms.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int SIGMA = 26;

/*-------- Input data --------*/
int N, K;
char text[MAX_N];
double prob_correct[SIGMA], prob_incorrect[SIGMA], prob_backspace[SIGMA];
/*-------- Dp --------*/
double dp[MAX_N];
double aux[MAX_N];
/*-------- --------*/

void read_input() {
    scanf("%d%d", &N, &K);
    scanf("%s", text);
    for(int i = 0; i < K; i++) {
        scanf("%lf%lf%lf", &prob_correct[i], &prob_incorrect[i], &prob_backspace[i]);
    }
}

void build_dp() {
    aux[0] = aux[1] = 1;
    for(int i = 1; i <= N; i++) {
        int val = text[i - 1] - 'a';
        aux[i + 1] = (aux[i] - prob_incorrect[val] * aux[i] - prob_backspace[val] * aux[i - 1]) / prob_correct[val];
        dp[i + 1] = (dp[i] + prob_correct[val] + (1 - dp[i - 1]) * prob_backspace[val] + (2 - dp[i]) * prob_incorrect[val]) / prob_correct[val];
    }
}

void write_output() {
    printf("%.12f", dp[N + 1] / aux[N + 1]);
}

int main() {
    read_input();
    build_dp();
    write_output();
    return 0;
}
