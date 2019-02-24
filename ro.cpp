/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ro.in", "r", stdin);
FILE *fout = freopen("ro.out", "w", stdout);

const int MAX_N = 1 + 2007;
const int MAX_M = 1 + 10000;
const int MAX_COMP_SIZE = 13;
const int MAX_MASK = (1 << 13);
const int MAX_INF = 2100000000;

/*----------------------------*/ /** General data */
int N, M;
int cost[MAX_N];
vector< int > graph[MAX_N];
bool isEdge[MAX_N][MAX_N];
/*----------------------------*/ /** Biconnected components */
bool criticalNode[MAX_N];
int level[MAX_N], biconnectedDP[MAX_N];
stack< pair< int,int > > Stack;

vector< vector< pair< int,int > > > comps;
vector< vector< int > > nodes;
vector< pair< int,int > > aux;
vector< int > aux2;
/*----------------------------*/ /** New graph stuff */
vector< int > newGraph[MAX_N + MAX_M];

int newIndex[MAX_N], critical[MAX_N];
int crtIndex, criticalCount;

int dp[MAX_N + MAX_M][MAX_COMP_SIZE][2];
int dpMask[MAX_N + MAX_M][MAX_COMP_SIZE][2];
/*----------------------------*/ /** Checking a biconnected component */
int active[MAX_N];
/*----------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &cost[i]);
    }
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        isEdge[u][v] = isEdge[v][u] = true;
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void addComponent(pair< int,int > p) {
    pair< int,int > now;
    do {
        now = Stack.top(); Stack.pop();
        aux2.push_back(now.first); aux2.push_back(now.second);
    }while(now != p);
    sort(aux2.begin(), aux2.end());
    aux2.erase(unique(aux2.begin(), aux2.end()), aux2.end());

    nodes.push_back(aux2);
    for(int i = 0; i < (int)aux2.size(); i++) {
        for(int j = i + 1; j < (int)aux2.size(); j++) {
            if(isEdge[aux2[i]][aux2[j]]) {
                aux.push_back(make_pair(aux2[i], aux2[j]));
            }
        }
    }
    comps.push_back(aux);
    aux.clear(); aux2.clear();

}

void biconnectedDFS(int node = 1, int father = 0) {
    biconnectedDP[node] = level[node];
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!level[*it]) {
            level[*it] = level[node] + 1;
            Stack.push(make_pair(node, *it));
            biconnectedDFS(*it, node);
            if(biconnectedDP[*it] >= level[node]) { /* if the node is critical */
                addComponent(make_pair(node, *it));
                criticalNode[node] = true;
            }
        }
    }

    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(*it != father) {
            biconnectedDP[node] = min(biconnectedDP[node], biconnectedDP[*it]);
        }
    }
}

void makeNewGraph() {
    for(int i = 1; i <= N; i++) {
        if(criticalNode[i]) {
            newIndex[i] = ++crtIndex;
            critical[++criticalCount] = i;
        }
    }

    for(int i = 0; i < (int)comps.size(); i++) {
        ++crtIndex;

        for(vector< int >::iterator it = nodes[i].begin(); it != nodes[i].end(); it++) {
            if(criticalNode[*it]) {
                newGraph[newIndex[*it]].push_back(crtIndex);
                newGraph[crtIndex].push_back(newIndex[*it]);
            }
        }
    }
}

void Switch(int id, int mask, bool state) {
    for(int i = 0; i < (int)nodes[id].size(); i++) {
        if(mask & (1 << i)) { /* we mark the "active" nodes */
            active[nodes[id][i]] = state;
        }
    }
}

bool checkPossibility(int id, int mask) {
    /* the function checks whether it is possible or not to cover all the edges of a biconnected component with a given bit-mask */

    Switch(id, mask, true);

    bool answer = true;

    for(vector< pair< int,int > >::iterator it = comps[id].begin(); it != comps[id].end(); it++) {
        if(!active[it->first] && !active[it->second]) { /* if we have an uncovered edge, the mask is not valid */
            answer = false; break;
        }
    }

    Switch(id, mask, false);

    return answer;
}

void treeDFS(int node = 1, int father = 0) {
    /* we approach the critical nodes and the biconnected components differently*/

    if(node <= criticalCount) { /* if we're dealing with a critical node */
        dp[node][0][0] = 0;
        dp[node][0][1] = cost[critical[node]];

        for(vector< int >::iterator it = newGraph[node].begin(); it != newGraph[node].end(); it++) {
            if(*it != father) { /* we look at it's sons */
                treeDFS(*it, node);
                int id = *it - criticalCount - 1; /* the index of the biconnected component */

                for(int i = 0; i < (int)nodes[id].size(); i++) {
                    if(nodes[id][i] == critical[node]) { /* we add the cost of the component's dp to the current one */
                        if(dp[*it][i][0] == MAX_INF) {
                            dp[node][0][0] = MAX_INF;
                        } else {
                            dp[node][0][0] += dp[*it][i][0];
                        }

                        dp[node][0][1] += dp[*it][i][1];
                        break;
                    }
                }
            }
        }
    } else { /* if we're dealing with a biconnected component */
        int id = node - criticalCount - 1; /* the index of the biconnected component */
        int LIMIT = (1 << (int)nodes[id].size()); /* the limit of the mask for dp */

        for(vector< int >::iterator it = newGraph[node].begin(); it != newGraph[node].end(); it++) {
            if(*it != father) {
                treeDFS(*it, node);
            }
        }

        for(int i = 0; i < (int)nodes[id].size(); i++) { /* we initialize the dp */
            dp[node][i][0] = dp[node][i][1] = MAX_INF;
        }

        for(int mask = 1; mask < LIMIT; mask++) { /* the mask can't be 0, because it's impossible to cover its edges */
            bool ok = checkPossibility(id, mask);
            if(!ok) { /* if the mask is not valid */
                continue;
            }
            Switch(id, mask, true);

            int crtCost = 0; /* we want to compute the cost of activating the current nodes */
            for(int i = 0; i < (int)nodes[id].size(); i++) {
                if(active[nodes[id][i]] && criticalNode[nodes[id][i]] == false) {
                    crtCost += cost[nodes[id][i]];
                }
            }

            for(vector< int >::iterator it = newGraph[node].begin(); it != newGraph[node].end(); it++) {
                if(*it != father) { /* we add the dp of the node's sons to the cost */
                    if(crtCost == MAX_INF) {
                        break;
                    }

                    int nodeID = critical[*it];
                    if(!active[nodeID]) {
                        if(dp[*it][0][0] == MAX_INF) {
                            crtCost = MAX_INF;
                        } else {
                            crtCost += dp[*it][0][0];
                        }
                    } else {
                        crtCost += dp[*it][0][1];
                    }
                }
            }

            if(crtCost != MAX_INF) {
                for(int i = 0; i < (int)nodes[id].size(); i++) {
                    if(active[nodes[id][i]]) {
                        if(crtCost < dp[node][i][1]) {
                            dp[node][i][1] = crtCost;
                            dpMask[node][i][1] = mask;
                        }
                    } else {
                        if(crtCost < dp[node][i][0]) {
                            dp[node][i][0] = crtCost;
                            dpMask[node][i][0] = mask;
                        }
                    }
                }
            }

            Switch(id, mask, false);
        }
    }
}

void reconstructPath(int node = 1, int father = 0) {
    if(node == 1) {
        if(dp[1][0][0] < dp[1][0][1]) {
            active[critical[node]] = false;
        } else {
            active[critical[node]] = true;
        }
    } else if(node <= criticalCount) {

    } else {
        int id = node - criticalCount - 1;
        for(int i = 0; i < (int)nodes[id].size(); i++) {
            if(nodes[id][i] == critical[father]) {
                int mask;
                if(!active[critical[father]]) {
                    mask = dpMask[node][i][0];
                } else {
                    mask = dpMask[node][i][1];
                }

                if(mask == 0) {printf("ERROR");}

                for(int j = 0; j < (int)nodes[id].size(); j++) {
                    if(mask & (1 << j)) {
                        active[nodes[id][j]] = true;
                    }
                }
                break;
            }
            if(i == (int)nodes[id].size() - 1) {printf("ERROR");}
        }
    }

    for(vector< int >::iterator it = newGraph[node].begin(); it != newGraph[node].end(); it++) {
            if(*it != father) {
                reconstructPath(*it, node);
            }
        }
}

void writeData() {
    printf("%d\n", min(dp[1][0][0], dp[1][0][1]));
    reconstructPath();
    for(int i = 1; i <= N; i++) {
        if(active[i]) {
            aux2.push_back(i);
        }
    }
    printf("%d\n", (int)aux2.size());
    for(vector< int >::iterator it = aux2.begin(); it != aux2.end(); it++) {
        printf("%d ", *it);
    }
}

int main() {
    readData();
    level[1] = 1; biconnectedDFS();
    makeNewGraph();
    treeDFS();
    writeData();
    return 0;
}
