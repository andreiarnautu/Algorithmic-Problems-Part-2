/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("razbunare.in", "r", stdin);
//FILE *fout = freopen("razbunare.out", "w", stdout);

const int kMaxN = 1 + 30;
const int kMaxL = 1 + 30000;
const int kMaxQ = 1 + 300000;
const int kMaxInf = 1e9;
const int kBufferSize = 100000;

/*-------- Input Parser --------*/
class InputParser {
public:
        char buffer[kBufferSize];
        int cursor;

        void GetBuffer() { cursor = 0; fread(buffer, 1, kBufferSize, stdin); }

        InputParser() { GetBuffer(); }

        bool IsDigit(char c) { return '0' <= c && c <= '9'; }

        InputParser& operator >>(int &number) {
            char sign = '+';
            while(!IsDigit(buffer[cursor])) {
                sign = buffer[cursor];
                if(++cursor == kBufferSize) {
                    GetBuffer();
                }
            }
            number = 0;
            while(IsDigit(buffer[cursor])) {
                number = number * 10 + buffer[cursor] - '0';
                if(++cursor == kBufferSize) {
                    GetBuffer();
                }
            }

            if(sign == '-') { number = -number; }
            return *this;
        }
} cin;
/*-------- Structures --------*/
struct Edge {
    int u, v, take_cost, skip_cost;
};
struct Query {
    int left, right, u, v, index;
};
/*-------- Input data --------*/
int N, L, Q;
int kSize;
std::vector<Edge > edges;
/*-------- Algorithm data --------*/
std::vector<Query > queries[kMaxQ / 10];
std::vector<std::vector<int > > aux_dp;
/*-------- Solution --------*/
std::vector<int > solution;
/*-------- --------*/

void ReadInput() {
    cin >> N >> L >> Q;
    kSize = 300; edges.resize(L);
    for(auto &edge : edges) {
        cin >> edge.u >> edge.v >> edge.take_cost >> edge.skip_cost;
        edge.u--; edge.v--;
    }
}

void UpdateDirected(std::vector<int > &dp, int u, int v, int cost) {
    dp[v] = std::min(dp[v], dp[u] + cost);
}

void UpdateUndirected(std::vector<int > &dp, int u, int v, int cost) {
    int aux = dp[v];
    UpdateDirected(dp, u, v, cost);
    std::swap(aux, dp[v]);
    UpdateDirected(dp, v, u, cost);
    std::swap(aux, dp[v]);
}

int BruteForce(const Query query) {
    std::vector<int > dp(N, kMaxInf); dp[query.u] = 0;

    int bonus = 0;
    for(int cursor = query.left; cursor <= query.right; cursor++) {
        auto &edge = edges[cursor];
        bonus += edge.skip_cost;
        UpdateUndirected(dp, edge.u, edge.v, edge.take_cost - edge.skip_cost);
    }

    return (dp[query.v] == kMaxInf) ? -1 : bonus + dp[query.v];
}

bool CompRight(Query a, Query b) {
    return a.right < b.right;
}

bool CompLeft(Query a, Query b) {
    return a.left > b.left;
}

void UpdateEdge(const Edge &edge, std::vector<std::vector<int > > &dp) {
    for(int i = 0; i < N; i++) {
        UpdateUndirected(dp[i], edge.u, edge.v, edge.take_cost - edge.skip_cost);
    }
}

void SolveBlock(int block_index) {
    std::vector<std::vector<int > > dp(N, std::vector<int >(N, kMaxInf));
    for(int i = 0; i < N; i++) { dp[i][i] = 0; }

    int block_end = kSize * (block_index + 1);

    ///  Rezolvam partea dreapta
    std::sort(queries[block_index].begin(), queries[block_index].end(), CompRight);
    for(int i = 0, cursor = block_end - 1, bonus = 0; i < (int)queries[block_index].size(); i++) {
        auto& query = queries[block_index][i];

        while(cursor < query.right) { cursor++; bonus += edges[cursor].skip_cost; UpdateEdge(edges[cursor], dp); }

        solution[query.index] += bonus;
        for(int j = 0; j < N; j++) {
            aux_dp[query.index][j] = dp[j][query.v];
        }
    }

    ///  Rezolvam partea stanga
    std::sort(queries[block_index].begin(), queries[block_index].end(), CompLeft);
    dp = std::vector<std::vector<int > >(N, std::vector<int >(N, kMaxInf));
    for(int i = 0; i < N; i++) { dp[i][i] = 0; }

    for(int i = 0, cursor = block_end, bonus = 0; i < (int)queries[block_index].size(); i++) {
        auto& query = queries[block_index][i];

        while(cursor > query.left) { cursor--; bonus += edges[cursor].skip_cost; UpdateEdge(edges[cursor], dp); }

        solution[query.index] += bonus;
        int dp_outcome = kMaxInf;
        for(int j = 0; j < N; j++) {
            if(aux_dp[query.index][j] != kMaxInf && dp[j][query.u] != kMaxInf) {
                dp_outcome = std::min(dp_outcome, aux_dp[query.index][j] + dp[j][query.u]);
            }
        }

        if(dp_outcome == kMaxInf) {
            solution[query.index] = -1;
        } else {
            solution[query.index] += dp_outcome;
        }
    }
}

void ProcessQueries() {
    solution.resize(Q);
    aux_dp = std::vector<std::vector<int > > (Q, std::vector<int >(N, 0));

    for(int i = 0; i < Q; i++) {
        Query query; cin >> query.u >> query.v >> query.left >> query.right; query.index = i;
        query.u--; query.v--; query.left--; query.right--;

        int left_block = query.left / kSize, right_block = query.right / kSize;
        if(left_block == right_block) {  ///  Daca are dimensiunea <= sqrt(L), il rezolvam cu brutul
            solution[i] = BruteForce(query);
        } else {  ///  Altfel, il adaugam in grupa aferenta
            queries[left_block].push_back(query);
        }
    }

    ///  Rezolvam acum bloc cu bloc query-urile
    for(int i = 0; i < kMaxQ / 10; i++) {
        if(!queries[i].empty()) {
            SolveBlock(i);
        }
    }
}

void WriteOutput() {
    for(auto i : solution) {
        printf("%d\n", i >= kMaxInf ? -1 : i);
    }
}

int main() {
    ReadInput();
    ProcessQueries();
    WriteOutput();
    return 0;
}
