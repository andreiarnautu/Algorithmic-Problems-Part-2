/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("undo.in", "r", stdin);
FILE *fout = freopen("undo.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 520;
const int MAX_M = 1 + 500000;

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

/*---------------------------------*/
int version[MAX_M];
int N, M;
/*---------------------------------*/
struct Edge {
    int vertex, x, y, z;
    Edge(const int vertex, const int x, const int y, const int z) {
        this->vertex = vertex; this->x = x; this->y = y; this->z = z;
    }
};

struct Query {
    int index, x, y;
    Query(const int index, const int x, const int y) {
        this->index = index; this->x = x; this->y = y;
    }
};

vector<Edge> G[MAX_M];
vector<Query> queries[MAX_M];
int queryAnswer[MAX_M];
int index;

int aib[MAX_N][MAX_N];
/*---------------------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
}

void solveOperations() {
    int now = 0;

    for(int i = 1; i <= M; ++i) {
        int op; cin.getInt(op);
        if(op == 1) {
            int x, y, z; cin.getInt(x); cin.getInt(y); cin.getInt(z);
            now++;
            version[now] = now;
            G[version[now - 1]].push_back(Edge(version[now], x, y, z));
        } else if(op == 2) {
            int x, y; cin.getInt(x); cin.getInt(y);
            index++;
            queries[version[now]].push_back(Query(index, x, y));
        } else {
            int x; cin.getInt(x);
            now++;
            version[now] = version[now - x - 1];
        }
    }
}

void updateAIB(int x, int y, int val) {
    for(int i = x; i <= N; i += (i & (-i))) {
        for(int j = y; j <= N; j += (j & (-j))) {
            aib[i][j] += val;
        }
    }
}

int queryAIB(int x, int y) {
    int answer = 0;
    for(int i = x; i > 0; i -= (i & (-i))) {
        for(int j = y; j > 0; j -= (j & (-j))) {
            answer += aib[i][j];
        }
    }
    return answer;
}

void DFS(int node = 0) {
    for(vector<Query>::iterator it = queries[node].begin(); it != queries[node].end(); ++it) {
        queryAnswer[it->index] = queryAIB(it->x, it->y);
    }

    for(vector<Edge>::iterator it = G[node].begin(); it != G[node].end(); it++) {
        updateAIB(it->x, it->y, it->z);
        DFS(it->vertex);
        updateAIB(it->x, it->y, -it->z);
    }
}

void writeData() {
    for(int i = 1; i <= index; ++i) {
        printf("%d\n", queryAnswer[i]);
    }
}

int main() {
    readData();
    solveOperations();
    DFS();
    writeData();
    return 0;
}
