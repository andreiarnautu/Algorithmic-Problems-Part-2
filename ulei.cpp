/**
  *  Worg
  */
#include <map>
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;
FILE *fin = freopen("ulei.in", "r", stdin);
FILE *fout = freopen("ulei.out", "w", stdout);

const int MAX_N = 1 + 15000;
const int MAX_TYPE = 1 + 15000;
const int bufferDim = 100000;

class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*---------------------------*/ /** General data */
int N, M;
int degree[MAX_N];
vector< pair< int,int > > graph[MAX_N], oil[MAX_N];
vector< pair< int,bool > > nodes[MAX_N];
/*---------------------------*/ /** Edge pairs */
vector< pair < int,int > > Map[MAX_N];

vector< pair< int,int > > typeCount;
vector< int > indexes[MAX_TYPE];
/*---------------------------*/ /** Eulerian cycle */
vector< int > mainCycle, crtCycle;
/*---------------------------*/

void readData() {
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= M; i++) {
        int u, v, type; cin.getInt(u); cin.getInt(v); cin.getInt(type);
        degree[u]++; degree[v]++;
        graph[u].push_back(make_pair(type, v));
        graph[v].push_back(make_pair(type, u));
        oil[u].push_back(make_pair(v, type));
        oil[v].push_back(make_pair(u, type));
        nodes[u].push_back(make_pair(v, true));
        nodes[v].push_back(make_pair(u, true));
    }
}

void writeVector(vector< int > &vec) {
    for(vector< int >::iterator it = vec.begin(); it != vec.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
}

bool compReversed(const pair< int,int > a, const pair< int,int > b) {
    return a.first > b.first;
}

void updatePosition(int pos) {
    typeCount[pos].first--;
    for(int i = pos; i < (int)typeCount.size() - 1; i++) {
        if(typeCount[i].first <= typeCount[i + 1].first) {
            swap(typeCount[i], typeCount[i + 1]);
        } else {
            break;
        }
    }
    while(typeCount.back().first <= 0) {
        typeCount.pop_back();
    }
}

void makeEdgePairs(const int node) {
    sort(graph[node].begin(), graph[node].end()); /* sorted by edge value */
    sort(oil[node].begin(), oil[node].end()); /* sorted by nodes' values */
    sort(nodes[node].begin(), nodes[node].end()); /* sorted by nodes' values */

    for(vector< pair< int,int > >::iterator it = graph[node].begin(); it != graph[node].end(); it++)  {
        indexes[it->first].push_back(it->second);
    }

    int crtCount = 1;
    for(int i = 1; i < (int)graph[node].size(); i++) {
        if(graph[node][i].first != graph[node][i - 1].first) {
            typeCount.push_back(make_pair(crtCount, graph[node][i - 1].first));
            crtCount = 1;
        } else {
            crtCount++;
        }
    }
    typeCount.push_back(make_pair(crtCount, graph[node].back().first));

    sort(typeCount.begin(), typeCount.end(), compReversed);

    for(int i = 1; i <= (int)graph[node].size() / 2; i++) {
        int typeA = typeCount[0].second;
        int typeB = typeCount[1].second;
        int nodeA = indexes[typeA].back(); indexes[typeA].pop_back();
        int nodeB = indexes[typeB].back(); indexes[typeB].pop_back();

        Map[node].push_back(make_pair(nodeA, nodeB));
        Map[node].push_back(make_pair(nodeB, nodeA));
        updatePosition(1);
        updatePosition(0);
    }
    sort(Map[node].begin(), Map[node].end());
    typeCount.clear();
}

int binarySearch(int node, int value) {
    int left = 0, right = (int)nodes[node].size() - 1, answer = 0;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(nodes[node][mid].first >= value) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return answer;
}

int getMap(int node, int before) {
    int left = 0, right = (int)Map[node].size() - 1, answer = 0;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(Map[node][mid].first >= before) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return Map[node][answer].second;
}

int getOil(int u, int v) {
    int answer = 0, left = 0, right = (int)oil[u].size() - 1;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(oil[u][mid].first >= v) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return oil[u][answer].second;
}

void deleteEdge(int u, int v) {
    degree[u]--; degree[v]--;
    nodes[u][binarySearch(u, v)].second = false;
    nodes[v][binarySearch(v, u)].second = false;
}

void getCycle(int start, vector< int > &cycle) {
    int nxtNode = 0;
    for(int i = 0; i < (int)nodes[start].size(); i++) {
        if(nodes[start][i].second == true) {
            nxtNode = nodes[start][i].first;
        }
    }
    deleteEdge(start, nxtNode);
    cycle.push_back(start); cycle.push_back(nxtNode);

    int now = nxtNode;
    int before = start;
    while(1) {
        nxtNode = getMap(now, before);
        int pos = binarySearch(now, nxtNode);

        if(nodes[now][pos].second == true) { /* if we can continue the cycle */
            cycle.push_back(nxtNode);
            deleteEdge(now, nxtNode);
            before = now;
            now = nxtNode;
        } else { /* we completed the current cycle */
            return;
        }
    }
}

void Attach(int pos) {
    /* the function attaches a new cycle to the main one */
    int edge_1, edge_2;
    if(pos == (int)mainCycle.size() - 1) {
        edge_1 = getOil(mainCycle[0], mainCycle[(int)mainCycle.size() - 2]);
        edge_2 = getOil(mainCycle[0], mainCycle[1]);
    } else {
        edge_1 = getOil(mainCycle[pos], mainCycle[pos - 1]);
        edge_2 = getOil(mainCycle[pos], mainCycle[pos + 1]);
    }

    int edge_3, edge_4;
    edge_4 = getOil(crtCycle[0], crtCycle[(int)crtCycle.size() - 2]);
    edge_3 = getOil(crtCycle[0],crtCycle[1]);

    if(edge_1 == edge_3 || edge_2 == edge_4) {
        reverse(crtCycle.begin(), crtCycle.end());
    }
    crtCycle.pop_back();
    mainCycle.insert(mainCycle.begin() + pos, crtCycle.begin(), crtCycle.end());
}

void getEulerianCycle() {
    getCycle(1, mainCycle); /* find the first cycle, which is going to be the main one */
    /* now we have to keep looking for cycles that can connect to the main one */

    bool found;
    do {
        found = false;
        for(int i = mainCycle.size() - 1; i >= 0; i--) {
            int node = mainCycle[i];
            if(degree[node] > 0) {
                getCycle(node, crtCycle);
                Attach(i);
                crtCycle.clear();
                found = true; break;
            }
        }
    }while(found);
}

void writeData() {
    for(vector< int >::iterator it = mainCycle.begin(); it != mainCycle.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
}

void clearData() {
    for(int i = 1; i <= N; i++) {
        graph[i].clear(); oil[i].clear(); nodes[i].clear(); Map[i].clear();
    }
    mainCycle.clear();
}

int main() {
    cin.getBuffer();
    int T;
    for(cin.getInt(T); T > 0; T--) {
        readData();
        for(int i = 1; i <= N; i++) {
            makeEdgePairs(i);
        }
        getEulerianCycle();
        writeData();
        clearData();
    }
}
