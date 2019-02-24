/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("secvente3.in", "r", stdin);
FILE *fout = freopen("secvente3.out", "w", stdout);

const long long LIMIT = 10000000;
const int MAX_N = 1 + 10000;

long long a, b, P, M;

struct type {
    int index, pos, sol;
    long long sum;
    type(const int &index, const int &pos, const long long &sum) {
        this->index = index; this->pos = pos; this->sum = sum;
    }
};

bool dupaPos(const type &a, const type &b) {
    return a.pos < b.pos;
}

bool dupaSum(const type &a, const type &b) {
    return a.sum < b.sum;
}

vector <type> vec;
int answer[MAX_N];

void readData() {
    scanf("%lld%lld%lld%lld", &a, &b, &P, &M);
    for(int i = 1; i <= M; ++i) {
        int pos; long long sum;
        scanf("%d%lld", &pos, &sum);
        vec.push_back(type(i, pos, sum));
    }

    sort(vec.begin(), vec.end(), dupaPos);
}

void getNumbers() {
    long long x = a, current = a;
    int index = 0;

    while(index < M && vec[index].pos - 1 == 0) {
        index++;
    }

    for(int i = 1; i <= LIMIT && index < M; ++i) {
        while(index < M && vec[index].pos - 1 == i) {
            vec[index].sum += current;
            index++;
        }
        x = (x * b) % P;
        current += x;
    }
}

void getAnswers() {
    long long x = a, current = a;
    int index = 0;

    for(int i = 1; i <= LIMIT && index < M; ++i) {
        while(index < M && vec[index].sum < current) {
            vec[index].sol = i - 1;
            index++;
        }
        x = (x * b) % P;
        current += x;
    }

    for(vector <type>::iterator it = vec.begin(); it != vec.end(); ++it) {
        answer[it->index] = it->sol;
    }
    for(int i = 1; i <= M; ++i) {
        printf("%d ", answer[i]);
    }
}


int main() {
    clock_t startTime = clock();

    readData();
    getNumbers();
    sort(vec.begin(), vec.end(), dupaSum);
    getAnswers();

    clock_t finishTime = clock();
  //  printf("%.3f", (float)(finishTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}
