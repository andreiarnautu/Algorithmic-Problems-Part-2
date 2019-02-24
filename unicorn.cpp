/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("unicorn.in", "r", stdin);
FILE *fout = freopen("unicorn.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 100000;

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
struct Pancake {
    int radius, value;
    Pancake() {
        this->radius = this->value = 0;
    }
    Pancake(const int radius, const int value) {
        this->radius = radius; this->value = value;
    }
};

int N;
Pancake pancakes[MAX_N];
/*---------------------------------*/
vector< int > sorted;
int maxSTree[MAX_N * 4], indexSTree[MAX_N * 4];
int after[MAX_N];
int totalValue[MAX_N];

vector< int > SOL;
/*---------------------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    sorted.push_back(0); /* for special purposes */

    for(int i = 1; i <= N; ++i) {
        int R, C; cin.getInt(R); cin.getInt(C);
        pancakes[i] = Pancake(R, C);
        sorted.push_back(R);
    }

    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
}

int Get(int value) {
    int left = 1, right = (int)sorted.size() - 1, answer = 1;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(sorted[mid] <= value) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}

void updateSTree(int node, int left, int right, int pos, int val, int index) {
    if(left == right) { /* if we reached a leaf of the tree */
        if(val >= maxSTree[node]) {
            maxSTree[node] = val;
            indexSTree[node] = index;
        }
    } else { /* otherwise */
        int leftSon = node * 2, rightSon = leftSon + 1, mid = (left + right) / 2;
        if(pos <= mid) {
            updateSTree(leftSon, left, mid, pos, val, index);
        } else {
            updateSTree(rightSon, mid + 1, right, pos, val, index);
        }

        if(maxSTree[rightSon] > maxSTree[node] ||
          (maxSTree[rightSon] == maxSTree[node] && indexSTree[rightSon] < indexSTree[node]) ) {
            maxSTree[node] = maxSTree[rightSon];
            indexSTree[node] = indexSTree[rightSon];
        }
        if(maxSTree[leftSon] > maxSTree[node] ||
          (maxSTree[leftSon] == maxSTree[node] && indexSTree[leftSon] < indexSTree[node]) ) {
            maxSTree[node] = maxSTree[leftSon];
            indexSTree[node] = indexSTree[leftSon];
        }
    }
}

int queryMax, queryIndex; /* the results of the query */

void querySTree(int node, int left, int right, int pos) {
    if(pos < 1) {
        return;
    }

    if(right <= pos) { /* if the current segment is completely in range, we update the results */
        if(queryMax < maxSTree[node] || (queryMax == maxSTree[node] && queryIndex > indexSTree[node])) {
            queryMax = maxSTree[node];
            queryIndex = indexSTree[node];
        }
    } else { /* otherwise, we have to split it */
        int leftSon = node * 2, rightSon = leftSon + 1, mid = (left + right) / 2;
        querySTree(leftSon, left, mid, pos);
        if(mid < pos) {
            querySTree(rightSon, mid + 1, right, pos);
        }
    }
}

void solveProblem() {
    for(int i = N; i > 0; --i) {
        queryMax = queryIndex = 0;

        int Radius = Get(pancakes[i].radius);

        querySTree(1, 1, sorted.size() - 1, Radius - 1);
        after[i] = queryIndex;
        totalValue[i] = queryMax + pancakes[i].value;

        updateSTree(1, 1, sorted.size() - 1, Radius, totalValue[i], i);
    }
}

void writeData() {
    int index = 0;
    for(int i = 1; i <= N; ++i) {
        if(totalValue[i] > totalValue[index]) {
            index = i;
        }
    }
    printf("%d ", totalValue[index]);

    while(index != 0) {
        SOL.push_back(index);
        index = after[index];
    }
    printf("%d\n", (int)SOL.size());
    for(int i = 0; i < (int)SOL.size(); i++) {
        printf("%d ", SOL[i]);
    }
    printf("\n");
}

int main() {
    readData();
    solveProblem();
    writeData();

    return 0;
}
