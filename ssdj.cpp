/**
  *  Worg
  */
#include <stack>
#include <cstdio>

using namespace std;
FILE *fin = freopen("ssdj.in", "r", stdin);
FILE *fout = freopen("ssdj.out", "w", stdout);

const int MAX_N = 1 + 1000;

/*-------- Input data --------*/
int N;
char matrix[MAX_N][MAX_N];
/*-------- Solving data --------*/
int dp[MAX_N][MAX_N];

struct my_struct {
    int height;
    int position;

    my_struct() {}

    my_struct(const int _height, const int _position) {
        this->height = _height;
        this->position = _position;
    }
};

stack< my_struct > my_stack;
/*-------- --------*/

void read_input() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%s", matrix[i] + 1);
    }
}

int get_solution() {
    int solution = 0;

    for(char crt_char = 'a'; crt_char <= 'z'; crt_char++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(matrix[i][j] >= crt_char) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][j] + 1;
                }
            }
        }

        for(int i = 2; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(dp[i][j] > 0) {
                    while(!my_stack.empty() && my_stack.top().height >= dp[i][j]) {
                        my_stack.pop();
                    }
                    my_stack.push(my_struct(dp[i][j], j));
                } else {
                    int crt_height = dp[i - 1][j] + 1;
                    while(!my_stack.empty() && my_stack.top().height >= crt_height) {
                        my_stack.pop();
                    }

                    while(!my_stack.empty()) {
                        if(matrix[i][j] == crt_char || matrix[i - my_stack.top().height][my_stack.top().position] == crt_char) {
                            solution ++;
                        }
                        my_stack.pop();
                    }
                }
            }

            while(!my_stack.empty()) {
                my_stack.pop();
            }
        }
    }

    return solution;
}

int main() {
    read_input();
    printf("%d", get_solution());
    return 0;
}
