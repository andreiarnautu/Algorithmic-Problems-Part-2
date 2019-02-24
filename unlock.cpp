/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("unlock.in", "r", stdin);
FILE *fout = freopen("unlock.out", "w", stdout);

const int MAX_N = 1 + 250;
const int buffer_dim = 1 + 100000;
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};

/*-------- Input reader --------*/
class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void get_buffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;

/*-------- Input data --------*/
int test_count;
int N, M, K;
int matrix[MAX_N][MAX_N];
/*-------- Disjoint sets --------*/
int TOTAL_ZEROES;
int disjoint_set[MAX_N][MAX_N];
int crt_size;

vector< pair< int,int > > to_be_united[MAX_N * MAX_N];

struct Node {
    int father;
    int size;
};

struct Operation {
    int timestamp;
    int id;
    Node old_value;
};

int crt_time;
Node nodes[MAX_N * MAX_N];
stack< Operation > operations;

bool SPECIAL_CONDITION;
/*-------- --------*/

void get_test_data() {
    cin >> N; cin >> M; cin >> K;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> matrix[i][j];
            TOTAL_ZEROES += (matrix[i][j] == 0);
        }
    }
}

bool in_matrix(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= M);
}

int get_root(int id) {
    if(id != nodes[id].father) {
        if(crt_time != 0) {
            operations.push(Operation{crt_time, id, nodes[id]});
        }
        return nodes[id].father = get_root(nodes[id].father);
    } else {
        return id;
    }
}

void unite(int id1, int id2) {
    if(id1 != id2) {
        if(crt_time > 0) {
            operations.push(Operation{crt_time, id1, nodes[id1]});
            operations.push(Operation{crt_time, id2, nodes[id2]});
        }
        nodes[id2].size += nodes[id1].size;
        nodes[id1].father = id2;
    }
}

void undo() {
    if(!operations.empty()) { /* nu vrem sa dezbinam zerourile initiale */
        int timestamp = operations.top().timestamp;
        while(!operations.empty() && operations.top().timestamp == timestamp) {
            Operation operation = operations.top(); operations.pop();
            nodes[operation.id] = operation.old_value;
        }
    }
}


void initialize() {
    /* resetam timpul */
    crt_time = 0;

    /* initializam nodurile */
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            disjoint_set[i][j] = j + (i - 1) * M;

            int id = disjoint_set[i][j];
            nodes[id].father = id;
            if(matrix[i][j] == 0) {
                nodes[id].size = 1;
            } else {
                nodes[id].size = 0;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            for(int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if(in_matrix(x, y) && matrix[i][j] == matrix[x][y]) {
                    unite(get_root(disjoint_set[x][y]), get_root(disjoint_set[i][j]));
                }
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            disjoint_set[i][j] = get_root(disjoint_set[i][j]);
            if(nodes[disjoint_set[i][j]].size == TOTAL_ZEROES) {
                SPECIAL_CONDITION = true;
            }
        }
    }

    /* facem perechi intre noduri (c,0) */
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(matrix[i][j] != 0) {
                for(int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(in_matrix(x, y) && (matrix[x][y] == 0)) {
                        to_be_united[matrix[i][j]].push_back(make_pair(disjoint_set[i][j], disjoint_set[x][y]));
                    }
                }
            }
        }
    }

    /* unim zerourile initiale */

    if(TOTAL_ZEROES == 1) {
        SPECIAL_CONDITION = true;
    }
}


bool try_color(int color) {
    bool result = false;

    crt_time ++;
    for(pair< int,int > p : to_be_united[color]) {
        int id1 = p.first;
        int id2 = p.second;
        unite(get_root(id1), get_root(id2));
        if(nodes[get_root(id2)].size == TOTAL_ZEROES) {
            result = true; break;
        }
    }

    undo();
    return result;
}

void clear_data() {
    TOTAL_ZEROES = 0;
    SPECIAL_CONDITION = false;
    crt_size = 0;
    for(int i = 1; i <= K; i++) {
        to_be_united[i].clear();
    }
    while(!operations.empty()) {
        operations.pop();
    }

}

int main() {
    cin.get_buffer();
    cin >> test_count;

    for(int i = 1; i <= test_count; i++) {
        get_test_data();
        initialize();
        int solution = 0;
        if(SPECIAL_CONDITION == true) {
            solution = K;
        } else {
            for(int i = 1; i <= K; i++) {
                solution += try_color(i);
            }
        }
        printf("%d\n", solution);
        clear_data();
    }

    return 0;
}
