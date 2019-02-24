/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::vector;
using std::make_pair;

FILE *fin = freopen("statiuni.in", "r", stdin);
FILE *fout = freopen("statiuni.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int buffer_dim = 1 + 100000;
const int MAX_INF = 0x3ffffff;

/*-------- Input Reader --------*/
class InputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- Input data --------*/
int N, K;
vector< int > graph[MAX_N];
/*-------- Dynammic programming --------*/
int root;
int degree[MAX_N];

pair<int, int > dp_subtree[MAX_N];
pair<int, int > dp_above[MAX_N];

bool checked[MAX_N];
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> N; cin >> K;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u; cin >> v;
        graph[u].push_back(v); graph[v].push_back(u);
        degree[u] ++; degree[v] ++;
    }
}

int GetRoot() {
    int answer = -1;
    for(int i = 1; i <= N; i++) {
        if(degree[i] > 1) {
            answer = i;
        }
    }
    return answer;
}

void InitializeDP() {
    for(int i = 1; i <= N; i++) {
        dp_subtree[i].first = dp_subtree[i].second = MAX_INF;
        dp_above[i].first = dp_above[i].second = MAX_INF;
    }
}

void Update(pair<int, int > &to, pair<int, int > from) {
    if(from.second <= to.first) {
        to.second = to.first;
        to.first = from.second;
    } else if(from.second <= to.second) {
        to.second = from.second;
    }

    if(from.first <= to.first) {
        to.second = to.first;
        to.first = from.first;
    } else if(from.first <= to.second) {
        to.second = from.first;
    }
}

void DfsSubtree(int node = root, int father = -1) {
    if(degree[node] == 1) {  //  Cu alte cuvinte daca nodul nu mai are fii
        dp_subtree[node].first = 0;
    } else {
        for(int son : graph[node]) {
            if(son != father) {
                DfsSubtree(son, node);
                pair<int, int > dp_son = dp_subtree[son];

                if(dp_son.first != MAX_INF) { dp_son.first ++; }
                if(dp_son.second != MAX_INF) { dp_son.second ++; }

                Update(dp_subtree[node], dp_son);
            }
        }
    }
}

void DfsAbove(int node = root, int father = -1) {
    if(degree[node] != 1) {
        //  Updatam fiii pe baza radacinii
        vector< int > best;

        pair<int, int > dp = dp_above[node];
        if(dp.first != MAX_INF) { dp.first ++; }
        if(dp.second != MAX_INF) { dp.second ++; }

        best.push_back(dp.first); best.push_back(dp.second);

        for(int son : graph[node]) {
            if(son != father) {
                pair<int, int > dp = dp_subtree[son];

                if(dp.first != MAX_INF) { dp.first += 2; }
                if(dp.second != MAX_INF) { dp.second += 2; }

                best.push_back(dp.first); best.push_back(dp.second);
            }
        }

        std::sort(best.begin(), best.end());

        for(int son : graph[node]) {
            if(son != father) {
                //  Marcam eventualele valori rezultate datorita lui son
                int i = 0;
                for(; i < 4; i++) {
                    if(best[i] == dp_subtree[son].first + 2) {
                        checked[i] = true; i++;
                        break;
                    }
                }
                for(; i < 4; i++) {
                    if(best[i] == dp_subtree[son].second + 2) {
                        checked[i] = true; break;
                    }
                }

                int chosen = 0;

                for(int i = 0; i < 4 && chosen < 2; i++) {
                    if(!checked[i]) {
                        if(chosen == 0) {
                            dp.first = best[i];
                        } else {
                            dp.second = best[i];
                        }
                        chosen ++;
                    }
                }

                Update(dp_above[son], dp);

                //  Resetam valorile din {checked}
                for(int i = 0; i < 4; i++) {
                    checked[i] = false;
                }
            }
        }

        //  Continuam parcurgerea
        for(int son : graph[node]) {
            if(son != father) {
                DfsAbove(son, node);
            }
        }
    } else {
        //  printf("Nu verificam fii nodului %d\n", node);
    }
}

void WriteDpSubtree() {
    printf("Radacina: %d\n", root);
    for(int i = 1; i <= N; i++) {
        printf("%d %d\n", dp_subtree[i].first, dp_subtree[i].second);
    }
    printf("/*-------- --------*/\n");
}

void WriteDpAbove() {
    for(int i = 1; i <= N; i++) {
        printf("%d %d\n", dp_above[i].first, dp_above[i].second);
    }
    printf("/*-------- --------*/\n");
}

void WriteOutput() {
    int answer = 0;
    for(int i = 1; i <= N; i++) {
        pair<int, int > dp = make_pair(MAX_INF, MAX_INF);
        Update(dp, dp_subtree[i]);
        Update(dp, dp_above[i]);

        if(dp.second <= K) {
            answer ++;
        }
    }

    printf("%d\n", answer);
}

int main() {
    ReadInput();
    if(N <= 2) {
        printf("%d\n", N);
    } else {
        root = GetRoot();
        InitializeDP();
        DfsSubtree();
        DfsAbove();

        //  WriteDpSubtree();
        //  WriteDpAbove();
        WriteOutput();
    }

    return 0;
}
