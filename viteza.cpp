/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb              push_back
#define leftSon         (node << 1)
#define rightSon        (node << 1) + 1
#define zeros(i)        (i) & (-i)

using namespace std;
FILE *fin = freopen("viteza.in", "r", stdin);
FILE *fout = freopen("viteza.out", "w", stdout);

const int MAX_N = 1 + 100000,
          MAX_LOG = 20;

struct data {

    int node, cost;

    data(const int &node, const int &cost) {

        this->node = node;
        this->cost = cost;
    }

    bool operator <(const data &other) const {

        return this->cost < other.cost;
    }
};

struct queryData {

    int a, b, limit, index;

    queryData(const int &a, const int &b, const int &limit, const int &index) {

        this->a = a;
        this->b = b;
        this->limit = limit;
        this->index = index;
    }

    bool operator <(const queryData &other) const {

        return this->limit < other.limit;
    }
};


vector < int > G[MAX_N];
vector < data > nodes;
vector < queryData > q;

bool checked[MAX_N];
int rmq[MAX_LOG][MAX_N << 1];
int list[MAX_N << 1], depth[MAX_N << 1], lg[MAX_N << 1], aib[MAX_N << 1], sol[MAX_N << 1], speedLimit[MAX_N], pos[MAX_N], firstPos[MAX_N], lastPos[MAX_N];
int n, m, listSize, seqLen;

void readData() {

    scanf("%d %d ", &n, &m);
    for(int i = 1; i < n; ++i) {

        int x, y;
        scanf("%d %d ", &x, &y);
        G[x].pb(y); G[y].pb(x);
    }
    for(int i = 1; i <= n; ++i) {

        int x;
        scanf("%d ", &x);
        nodes.pb(data(i, x));
        speedLimit[i] = x;
    }
    for(int i = 1; i <= m; ++i) {

        int x, y, z;
        scanf("%d %d %d ", &x, &y, &z);
        q.pb(queryData(x, y, z, i));
    }
}

void update(int pos, int val) {

    for(; pos <= n << 1; pos += zeros(pos))
        aib[pos] += val;
}

int compute(int pos) {

    int ret = 0;
    for(; pos; pos -= zeros(pos))
        ret += aib[pos];
    return ret;
}

void eulerianDfs(int node, int level) {

    checked[node] = true;
    list[++listSize] = node;
    depth[listSize] = level;
    pos[node] = listSize;

    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!checked[*it]) {

            eulerianDfs(*it, level + 1);
            list[++listSize] = node;
            depth[listSize] = level;
        }
}

void getRMQ() {

    for(int i = 2; i <= listSize; ++i)
        lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= listSize; ++i)
        rmq[0][i] = i;

    for(int i = 1; (1 << i) < listSize; ++i) {

        int maxPos = listSize - (1 << i) + 1;
        for(int j = 1; j <= maxPos; ++j)
            rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
    }
}

int LCA(int x, int y) {

    int a = pos[x], b = pos[y];
    if(a > b)
        swap(a, b);

    int level = lg[b - a + 1];
    return (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
}

void dfs(int node) {

    checked[node] = true;
    firstPos[node] = ++seqLen;

    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!checked[*it])
            dfs(*it);

    lastPos[node] = ++seqLen;
}

int main() {

    readData();
    eulerianDfs(1, 0);
    getRMQ();
    for(int i = 1; i <= n; ++i)
        checked[i] = false;
    dfs(1);
    sort(nodes.begin(), nodes.end());
    sort(q.begin(), q.end());

    int position = 0;
    for(vector < queryData >::iterator it = q.begin(); it != q.end(); ++it) {

        while(position < nodes.size() && nodes[position].cost <= it->limit) {

            update(firstPos[nodes[position].node], 1);
            update(lastPos[nodes[position].node], -1);
            ++position;
        }

        int ancestor = LCA(it->a, it->b);

        sol[it->index] = compute(firstPos[it->a]) - compute(firstPos[ancestor] - 1) + compute(firstPos[it->b]) - compute(firstPos[ancestor] - 1);
        if(speedLimit[ancestor] <= it->limit)
            --sol[it->index];
    }

    for(int i = 1; i <= m; ++i)
        printf("%d\n", sol[i]);
    return 0;
}
