/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using std::pair;

FILE *fin = freopen("pitici3.in", "r", stdin);
FILE *fout = freopen("pitici3.out", "w", stdout);

const int kMaxN = 1 + 2000;
const int kMaxInf = 1e9;

/*-------- Input data --------*/
int N;
pair<int, int > data[kMaxN];
int pit_height;
/*-------- Dp --------*/
int dp[kMaxN];
int h_sum;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &data[i].first, &data[i].second);
        h_sum += data[i].first;
    }
    scanf("%d", &pit_height);
}

bool comp(pair<int, int > a, pair<int, int > b) {
    return a.first + a.second < b.first + b.second;
}

int RunDp() {
    int escaped = 0;
    dp[0] = 0;

    for(int i = 1; i <= N; i++) {
        dp[i] = kMaxInf;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = escaped; j >= 0; j--) {
            if(h_sum - dp[j] + data[i].second >= pit_height) {
                dp[j + 1] = std::min(dp[j + 1], dp[j] + data[i].first);
            }
        }
        if(dp[escaped + 1] != kMaxInf) {
            escaped ++;
        }
    }

    return escaped;
}

int main() {
    ReadInput();
    std::sort(data + 1, data + N + 1, comp);
    printf("%d", RunDp());
    return 0;
}
