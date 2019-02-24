/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

FILE *fin = freopen("soc2.in", "r", stdin);
FILE *fout = freopen("soc2.out", "w", stdout);

const int MAX_N = 1 + 256;

/*-------- Input data --------*/
int N, M;
int money[MAX_N];
int adj[MAX_N][MAX_N];
vector<int > graph[MAX_N];
/*-------- Node Ordering --------*/
vector<int > ordering;

int neighbours_before[MAX_N];
int common_neighbours[MAX_N][MAX_N];
bool chosen[MAX_N];
/*-------- Tree --------*/
int crt_index;
int main_node[MAX_N];

vector<int > tree[MAX_N];
vector<int > node_list[MAX_N];

int in_tree_node[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
/*-------- Reconstructing Solution --------*/
int ready[MAX_N];
/*-------- --------*/


void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &money[i]);
    }
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = true;
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void GetCommonNeighbours() {
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            for(int u : graph[i]) {
                if(u != j && adj[u][j]) {
                    common_neighbours[i][j] ++; common_neighbours[j][i] ++;
                }
            }
        }
    }
}

void GetNodeOrdering() {
    GetCommonNeighbours();

    for(int i = 1; i <= N; i++) {
        for(int node = 1; node <= N; node ++) {
            if(!chosen[node]) {
                bool ok = true;
                //  Vrem sa vedem daca putem pune nodul {node} pe pozitia curenta
                int neighbour_count = 0;
                for(int neighbour : graph[node]) {
                    if(!chosen[neighbour]) {
                        neighbour_count ++;
                    }
                }

                for(int neighbour : graph[node]) {
                    if(!chosen[neighbour] && common_neighbours[node][neighbour] != neighbour_count - 1) {
                        ok = false; break;
                    }
                }

                if(ok == true) {
                    ordering.push_back(node);
                    for(int u : graph[node]) {
                        for(int v : graph[node]) {
                            common_neighbours[u][v] --;
                        }
                    }
                    chosen[node] = true;
                    neighbours_before[node] = neighbour_count;
                    break;
                }
            }
        }
    }

    std::reverse(ordering.begin(), ordering.end());
}

void BuildTree() {
    //  Tratam separat primul nod
    crt_index ++;
    node_list[crt_index].push_back(ordering[0]);
    main_node[crt_index] = ordering[0];
    in_tree_node[crt_index][ordering[0]] = true;

    for(int i = 1; i < (int)ordering.size(); i++) {
        int node = ordering[i];

        for(int j = 1; j <= crt_index; j++) {
            int count = 0;
            bool ok = true;
            for(int x : node_list[j]) {
                if(adj[node][x]) {
                    count ++;
                }
            }

            if(count == neighbours_before[node]) {
                //  Am gasit nodul de care ne vom lega
                crt_index ++;
                for(int x : node_list[j]) {
                    if(adj[node][x]) {
                        node_list[crt_index].push_back(x);
                        in_tree_node[crt_index][x] = true;
                    }
                }
                node_list[crt_index].push_back(node);
                in_tree_node[crt_index][node] = true;
                main_node[crt_index] = node;

                tree[j].push_back(crt_index);
                //printf("Muchie %d -> %d\n", j, crt_index);

                break;
            }
        }
    }
}

void DFS(int node = 1) {
    for(int son : tree[node]) {
        DFS(son);  //  Rezolvam intai fiii
    }

    dp[node][0] = 0;
    for(int x : node_list[node]) {
        dp[node][x] = money[x];
    }

    for(int x : node_list[node]) {
        //  Adaugam la dp[node][x] pe baza fiilor
        for(int son : tree[node]) {
            int bonus_value = 0;

            if(in_tree_node[son][x]) {  //  Daca nodul x se gaseste si in fiul curent
                bonus_value = dp[son][x] - money[x];
            } else {  //  Altfel, daca nu se gaseste
                bonus_value = dp[son][0];  //  Luam in calcul si cazul in care nu alegem niciun nod din fiu
                for(int y : node_list[son]) {
                    if(!in_tree_node[node][y]) {
                        bonus_value = std::max(bonus_value, dp[son][y]);
                    }
                }
            }

            dp[node][x] += bonus_value;
        }
    }

    //  Ne ocupam si de dp[node][0]
    for(int son : tree[node]) {
        int bonus_value = dp[son][0];
        for(int y : node_list[son]) {
            if(!in_tree_node[node][y]) {
                bonus_value = std::max(bonus_value, dp[son][y]);
            }
        }
        dp[node][0] += bonus_value;
    }
}

int GetMaxValue(int node = 1) {
    int value = dp[node][0], chosen_node = 0;  //  Presupunem ca nu alegem niciun nod din grupul curent

    for(int x : node_list[node]) {
        if(ready[x] && dp[node][x] > value) {
            value = dp[node][x];
            chosen_node = x;
        }
    }

    if(chosen_node != 0) {
        ready[chosen_node] = 1;
    }

    for(int x : node_list[node]) {
        if(x != chosen_node) {
            ready[x] = false;
        }
    }
    for(int son : tree[node]) {
        GetMaxValue(son);
    }

    return value;
}

void WriteOutput(int solution) {
    printf("%d\n", solution);

    int count_chosen = 0;
    for(int i = 1; i <= N; i++) {
        if(ready[i] == 1) {
            count_chosen ++;
        }
    }

    printf("%d\n", count_chosen);
    for(int i = 1; i <= N; i++) {
        if(ready[i] == 1) {
            printf("%d ", i);
        }
    }
}

int main() {
    ReadInput();
    GetNodeOrdering();
    BuildTree();
    DFS();

    for(int i = 0; i <= N; i++) {
        ready[i] = 2;  //  Nu marcam nodurile nici ca fiind folosite, nici ca fiind nefolosite
    }
    int max_value = GetMaxValue();
    WriteOutput(max_value);
    return 0;
}
