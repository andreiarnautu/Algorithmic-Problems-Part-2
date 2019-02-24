/**
  *  Worg
  */
#include <cstdio>
#include <vector>
FILE *fin = freopen("soc.in", "r", stdin);
FILE *fout = freopen("soc.out", "w", stdout);

const int kMaxN = 1 + 256;

/*-------- Input data --------*/
int N, M;
int money[kMaxN];
bool adjacent[kMaxN][kMaxN];
/*-------- Solution --------*/
std::vector<int > solution;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &money[i]);
    }
    for(int i = 0; i < M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adjacent[u][v] = adjacent[v][u] = true;
    }
}

void GetComplementary() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i != j) {
                adjacent[i][j] ^= true;
            }
        }
    }
}

void DFS(std::vector<int > &available, int node, std::vector<int > &component, int componentNumber) {
    component[node] = componentNumber;
    for(int i = 1; i <= N; i++) {
        if(adjacent[node][i] && available[i] && !component[i]) {
            DFS(available, i, component, componentNumber);
        }
    }
}

void Compute(std::vector<int > &nodes, std::vector<int > &independentSet, std::vector<int > &clique, int &maxIndependentSet, int &maxClique) {
    if(nodes.size() == 1) {  //  If the graph has only one node
        independentSet.push_back(nodes.back()); clique.push_back(nodes.back());
        maxIndependentSet = maxClique = money[nodes.back()];
    } else {
        //  Compute connectec components
        std::vector<int > component(kMaxN, 0), available(kMaxN, 0);
        int componentCount = 0;
        for(auto node : nodes) {
            available[node] = true;
        }
        for(auto node : nodes) {
            if(!component[node]) {
                ++componentCount;
                DFS(available, node, component, componentCount);
            }
        }

        if(componentCount == 1) {
            //  The graph is the complementary of a co-graph
            GetComplementary();
            Compute(nodes, clique, independentSet, maxClique, maxIndependentSet);
            GetComplementary();
        } else {
            for(int i = 1; i <= N; i++) {
                if(available[i] && component[i] != 0) {
                    std::vector<int > newSet, newIndependentSet, newClique;
                    int newMaxIndependentSet = 0, newMaxClique = 0;
                    newSet.push_back(i);
                    for(int j = i + 1; j <= N; j++) {
                        if(available[j] && component[j] == component[i]) {
                            newSet.push_back(j); component[j] = 0;
                        }
                    }
                    Compute(newSet, newIndependentSet, newClique, newMaxIndependentSet, newMaxClique);

                    //  Update maximum independent set
                    maxIndependentSet += newMaxIndependentSet;
                    for(auto node : newIndependentSet) {
                        independentSet.push_back(node);
                    }
                    //  Update maximum clique
                    if(newMaxClique > maxClique) {
                        maxClique = newMaxClique;
                        clique = newClique;
                    }
                }
            }

        }
    }
}

void Solve() {
    std::vector<int > list, independentSet, clique;
    for(int i = 1; i <= N; i++) {
        list.push_back(i);
    }

    int maxIndependentSet = 0, maxClique = 0;
    Compute(list, independentSet, clique, maxIndependentSet, maxClique);

    printf("%d\n%d\n", maxClique, (int)clique.size());
    for(auto node : clique) {
        printf("%d ", node);
    }
}

int main() {
    ReadInput();
    Solve();
    return 0;
}
