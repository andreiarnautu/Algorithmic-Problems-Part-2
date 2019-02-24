/**
  *  Worg
  */
#include <deque>
#include <cstdio>

FILE *fin = freopen("deque.in", "r", stdin); FILE *fout = freopen("deque.out", "w", stdout);

const int MAX_N = 5e6 + 5;

/*-------- Data --------*/
int arr[MAX_N];
std::deque<int > deq;
/*-------- --------*/

int main() {
  int n, k; scanf("%d%d", &n, &k);

  long long ans = 0;
  for(int i = 1; i <= n; i++) {
    scanf("%d", &arr[i]);

    //  Pop elements in the back
    while(!deq.empty() && arr[deq.back()] >= arr[i]) {
      deq.pop_back();
    }
    deq.push_back(i);

    //  Make sure that the deque doesn't contain elements out of range
    if(!deq.empty() && i - deq.front() == k) {
      deq.pop_front();
    }

    //  Update solution
    if(i >= k) {
      ans += arr[deq.front()];
    }
  }

  printf("%lld\n", ans);
  return 0;
}