/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
FILE *fin = freopen("semne.in", "r", stdin);
FILE *fout = freopen("semne.out", "w", stdout);

const int kMaxN = 50000;

/*-------- Data --------*/
long long S, currentSum;
int N, value[kMaxN];

std::vector<int > plus, minus;
char sign[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d%lld", &N, &S);
    for(int i = 0; i < N; i++) {
        scanf("%d", &value[i]);
        if(S > currentSum) {
            sign[i] = '+'; currentSum += value[i]; plus.push_back(i);
        } else {
            sign[i] = '-'; currentSum -= value[i]; minus.push_back(i);
        }
    }
}

void MakeChanges() {
    std::srand(std::time(NULL));
    while(currentSum != S) {
        if(currentSum > S) {
            int x = rand() % plus.size();
            currentSum -= 2 * value[plus[x]];
            minus.push_back(plus[x]); sign[plus[x]] = '-';
            plus[x] = plus.back(); plus.pop_back();
        } else {
            int x = rand() % minus.size();
            currentSum += 2 * value[minus[x]];
            plus.push_back(minus[x]); sign[minus[x]] = '+';
            minus[x] = minus.back(); minus.pop_back();
        }
    }
}

int main() {
    ReadInput();
    MakeChanges();
    printf("%s\n", sign);
    return 0;
}
