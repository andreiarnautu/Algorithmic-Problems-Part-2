/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("router.in", "r", stdin);
FILE *fout = freopen("router.out", "w", stdout);

vector< pair< int,int > > SOL;

int N;

void Test_3() {
    int BLOCK = 400;
    int how_many = N / BLOCK + 1;

    for(int i = 1; i <= N; i++) {
        SOL.push_back(make_pair(i, 2 * N + i / BLOCK + 1));
        SOL.push_back(make_pair(2 * N + how_many + i / BLOCK + 1, N + i));
    }
    for(int i = 2*N + 1; i <= 2*N + how_many; i++) {
        for(int j = 2*N + how_many + 1; j <= 2*N + how_many*2; j++) {
            SOL.push_back(make_pair(i, j));
        }
    }

    printf("%d %d\n", 2 * N + how_many * 2, (int)SOL.size());
    for(int i = 0; i < (int)SOL.size(); i++) {
        printf("%d %d\n", SOL[i].first, SOL[i].second);
    }
}

int main() {
    scanf("%d", &N);
    Test_3();
}
