/**
  *  Worg
  */
#include <queue>
#include <stack>
#include <cstdio>

FILE *fin = freopen("queue.in", "r", stdin); FILE *fout = freopen("queue.out", "w", stdout);

const int MAX_LEN = 20;

/*-------- Data --------*/
int n;
char s[MAX_LEN];

std::stack<int > stk[2];
/*-------- --------*/

int GetValue() {
  int ret = 0;

  for(int i = 10; '0' <= s[i] && s[i] <= '9'; i++) {
    ret = ret * 10 + s[i] - '0';
  }

  return ret;
}

int main() {
  scanf("%d", &n);

  for(int i = 1; i <= n; i++) {
    scanf("%s", s);

    if(s[1] == 'u') {
      int value = GetValue();
      stk[0].push(value);

      printf("%d: read(%d) push(1,%d)\n", i, value, value);
    } else {
      printf("2: ");
      if(stk[1].empty()) {
        while(!stk[0].empty()) {
          int value = stk[0].top(); stk[0].pop(); printf("pop(1) ");

          stk[1].push(value); printf("push(2,%d) ", value);
        }
      }

      int value = stk[1].top(); stk[1].pop(); printf("pop(2) ");
      printf("write(%d)\n", value);
    }
  }

  return 0;
}