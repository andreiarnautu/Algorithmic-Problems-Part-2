/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("specsort.in", "r", stdin);
FILE *fout = freopen("specsort.out", "w", stdout);

const int MAX_N = 1 + 50000 + 1;

/*-------- Input data --------*/
int N;
vector< int > permutation;
/*-------- Sorting data --------*/
int where[MAX_N];
vector< int > crt_substring;
vector< vector< int > > substrings;

bool to_front[MAX_N];
vector< int > new_permutation;
/*-------- --------*/

void read_input() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int x; scanf("%d", &x);
        permutation.push_back(x);
    }
}

int get_substrings() {
    for(int i = 0; i < N; i++) {
        where[permutation[i]] = i;
    }

    int last = 0;
    for(int crt = 1; crt <= N; crt++) {
        if(where[crt] > where[crt + 1]) {
            for(int i = last; i <= crt; i++) {
                crt_substring.push_back(i);
            }
            substrings.push_back(crt_substring);
            crt_substring.clear();
            last = crt + 1;
        }
    }

    return (int)substrings.size();
}

void construct_new_permutation() {
    for(int i = 0; i < (int)substrings.size(); i += 2) {
        for(int elem : substrings[i]) {
            to_front[elem] = true;
        }
    }

    for(int elem : permutation) {
        if(to_front[elem]) {
            new_permutation.push_back(elem);
        }
    }
    for(int elem : permutation) {
        if(!to_front[elem]) {
            new_permutation.push_back(elem);
        }
    }
}

void write_permutation() {
    for(int elem : permutation) {
        printf("%d ", elem);
    }
    printf("\n");
}

void reset_data() {
    substrings.clear();
    new_permutation.clear();
    for(int i = 1; i <= N; i++) {
        to_front[i] = false;
    }
}

void solve_problem() {
    while(get_substrings() > 1) {
        construct_new_permutation();
        permutation = new_permutation;
        write_permutation();
        reset_data();
    }
}

int main() {
    read_input();
    solve_problem();
    return 0;
}
