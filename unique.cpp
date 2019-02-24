/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("unique.in", "r", stdin);
FILE *fout = freopen("unique.out", "w", stdout);

const int MAX_N = 1 + 100000 + 1;

/*-------- Input data --------*/
int test_count;
int N;
int vec[MAX_N];
/*-------- Algorithm data --------*/
int father[MAX_N], size[MAX_N], different_values[MAX_N];
int last_appearance[MAX_N];

stack< int > my_stack;
/*-------- --------*/

void read_input() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &vec[i]);
    }
}

void initialize() {
    vec[N + 1] = N + 1;
    for(int i = 1; i <= N + 1; i++) {
        father[i] = i;
        size[i] = 1;
        different_values[i] = 0;
        last_appearance[i] = 0;
    }

    size[N + 1] = 0;

    while(!my_stack.empty()) {
        my_stack.pop();
    }
}

int group(int id) {
    if(id != father[id]) {
        father[id] = group(father[id]);
    }
    return father[id];
}

void unite(int u, int v) {
    u = group(u);
    v = group(v);

    father[v] = u;
    size[u] += size[v];
}

void run_algorithm() {
    int solution = 0;

    for(int i = 1; i <= N + 1; i++) {
        int different_count = 0;
        while(!my_stack.empty() && vec[my_stack.top()] < vec[i]) {      /* Eliminam elemente din stiva daca sunt mai mici decat
                                                                           cel curent */
            int current = my_stack.top(); my_stack.pop();

            different_count += different_values[group(current)];

            if(different_count == vec[current]) {
                int index = 0;
                if(!my_stack.empty()) {
                    index = my_stack.top();
                }
                solution = max(solution, i - 1 - index);
            }

            unite(i, current);
        }

        my_stack.push(i);
        different_values[i] = 1 + different_count;

        if(last_appearance[vec[i]] != 0) {                          /* Pentru a nu numara decat o singura data o valoare. */
            different_values[group(last_appearance[vec[i]])] --;
        }
        last_appearance[vec[i]] = i;
    }

    printf("%d\n", solution);
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        read_input();
        initialize();
        run_algorithm();
    }
}
