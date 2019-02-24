/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define lsb(i) ((i) & (-i))

using namespace std;
FILE *fin = freopen("qxy.in", "r", stdin);
FILE *fout = freopen("qxy.out", "w", stdout);

const int MAX_N = 1 + 10000;
const int MAX_Q = 1 + 100000;
const int MAX_VAL = 1 + 1000;
const int bufferDim = 5000;

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

struct Query {
    int index, val1, val2;
    Query(const int &index, const int &val1, const int &val2) {
        this->index = index; this->val1 = val1; this->val2 = val2;
    }
};

vector <Query> vec[MAX_N];
int a[MAX_N];
int N, Q;

int AIB[MAX_VAL + 1];
short int queryAnswer[MAX_Q];

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(a[i]);
    }
    cin.getInt(Q);
    for(int i = 1; i <= Q; ++i) {
        int left, right, x, y;
        cin.getInt(left); cin.getInt(right); cin.getInt(x); cin.getInt(y);
        vec[right].push_back(Query(i, y + 1, x));
        vec[left - 1].push_back(Query(i, x, y + 1));
    }
}

void updateAIB(int pos, int val) {
    for(; pos <= MAX_VAL; pos += lsb(pos)) {
        AIB[pos] += val;
    }
}

int queryAIB(int pos) {
    int answer = 0;
    for(; pos; pos -= lsb(pos)) {
        answer += AIB[pos];
    }
    return answer;
}

void solveProblem() {
    for(int i = 1; i <= N; ++i) {
        updateAIB(a[i] + 1, 1);
        for(vector <Query>::iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
            int x = queryAIB(it->val1);
            int y = queryAIB(it->val2);
            queryAnswer[it->index] += x - y;
        }
    }
}

void writeData() {
    for(int i = 1; i <= Q; ++i) {
        printf("%d\n", queryAnswer[i]);
    }
}

int main() {
    readData();
    solveProblem();
    writeData();
    return 0;
}
