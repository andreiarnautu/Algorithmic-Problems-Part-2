/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("zaharel.in", "r", stdin); FILE *fout = freopen("zaharel.out", "w", stdout);

/*--------- Data --------*/
int N, M;
std::vector<std::pair<int, int > > red, blue, ansRed, ansBlue;
/*--------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    red = blue = std::vector<std::pair<int, int > >(N + 1);

    for(int i = 0; i < M; i++) {
        int u, v; char c; scanf("%d %d %c", &u, &v, &c);

        if(c == 'R') {
            red[u] = {u, v};
        } else {
            blue[v] = {u, v};
        }
    }
}

void BuildAns() {
    std::vector<bool > used(N + 1, false);

    int crt = 1;

    while(!used[crt]) {
        used[crt] = true;
        crt = blue[red[crt].second].first;
    }

    while(used[crt]) {
        used[crt] = false;
        ansRed.emplace_back(red[crt]);
        ansBlue.emplace_back(blue[red[crt].second]);

        crt = blue[red[crt].second].first;
    }
}

void WriteOutput() {
    printf("%d\n", (int)ansRed.size());
    for(auto& itr : ansRed) {
        printf("%d %d ", itr.first, itr.second);
    }
    printf("\n");
    for(auto& itr : ansBlue) {
        printf("%d %d ", itr.first, itr.second);
    }
}

int main() {
    ReadInput();

    BuildAns();

    WriteOutput();

	return 0;
}
