/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

FILE *fin = freopen("plimbare3.in", "r", stdin); FILE *fout = freopen("plimbare3.out", "w", stdout);

const int kMaxN = 2e5 + 5;

/*-------- Input data --------*/
int N;
std::vector<std::vector<std::pair<int, int > > > graph;
/*-------- Dp data --------*/
int up[kMaxN], down[kMaxN][3], dpUp[kMaxN], dpDown[kMaxN][2];
int now[3], now2[2];

int answer[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N); graph.resize(N + 1);

    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);

        graph[u].push_back({v, i}); graph[v].push_back({u, i});
    }
}

void DFS_1(int node, int father) {
    for(auto& edge : graph[node]) {
        int son = edge.first;
        if(son == father) continue;

        DFS_1(son, node);

        int x = down[son][0] + 1;

        if(x > down[node][0]) {
            down[node][2] = down[node][1]; down[node][1] = down[node][0]; down[node][0] = x;
        } else if(x > down[node][1]) {
            down[node][2] = down[node][1]; down[node][1] = x;
        } else if(x > down[node][2]) {
            down[node][2] = x;
        }

        x = dpDown[son][0];

        if(x > dpDown[node][0]) {
            dpDown[node][1] = dpDown[node][0]; dpDown[node][0] = x;
        } else if(x > dpDown[node][1]) {
            dpDown[node][1] = x;
        }
    }

    int x = down[node][0] + down[node][1];

    if(x > dpDown[node][0]) {
        dpDown[node][1] = dpDown[node][0]; dpDown[node][0] = x;
    } else if(x > dpDown[node][1]) {
        dpDown[node][1] = x;
    }
}

void DFS_2(int node, int father) {
    now[0] = down[node][0]; now[1] = down[node][1]; now[2] = down[node][2];

    if(up[node] > now[0]) {
        now[2] = now[1]; now[1] = now[0]; now[0] = up[node];
    } else if(up[node] > now[1]) {
        now[2] = now[1]; now[1] = up[node];
    } else if(up[node] > now[2]) {
        now[2] = up[node];
    }

    now2[0] = now2[1] = 0;
    for(auto& edge: graph[node]) {
        int son = edge.first, index = edge.second;
        if(son == father) continue;

        if(dpDown[son][0] > now2[0]) {
            now2[1] = now2[0]; now2[0] = dpDown[son][0];
        } else if(dpDown[son][0] > now2[1]) {
            now2[1] = dpDown[son][0];
        }
    }


    for(auto& edge : graph[node]) {
        int son = edge.first, index = edge.second;
        if(son == father) continue;

        //  Update answer
        int k = dpUp[node];

        if(now2[0] == dpDown[son][0]) {
            k = std::max(k, now2[1]);
        } else {
            k = std::max(k, now2[0]);
        }

        if(now[0] == down[son][0] + 1) {
            k = std::max(k, now[1] + now[2]);
        } else if(now[1] == down[son][0] + 1) {
            k = std::max(k, now[0] + now[2]);
        } else {
            k = std::max(k, now[0] + now[1]);
        }

        answer[index] = 1 + k + dpDown[son][0];

        //  Update up
        if(now[0] == down[son][0] + 1) {
            up[son] = now[1] + 1;
        } else {
            up[son] = now[0] + 1;
        }

        //  Update dpUp
        dpUp[son] = k;
    }

    for(auto& edge : graph[node]) {
        int son = edge.first;
        if(son == father) continue;

        DFS_2(son, node);
    }
}

void WriteOutput() {
    for(int i = 1; i < N; i++) {
        printf("%d\n", answer[i]);
    }
}

int main() {
    ReadInput();

    DFS_1(1, 0);

    DFS_2(1, 0);

    WriteOutput();
	return 0;
}
