/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("undo2.in", "r", stdin);
FILE *fout = freopen("undo2.out", "w", stdout);

const int MAX_N = 1 + 200000;

vector< int > Public;
vector< int > Stack[MAX_N];
int Index;

void checkDeleted(const int &value) {
    while((int)Public.size() > Index) {
        Stack[Public.back()].pop_back();
        Public.pop_back();
    }
}

void insertNew(const int &value) {
    checkDeleted(value);
    Stack[value].push_back(++ Index);
    Public.push_back(value);
}

int countHowMany(const int &value) {
    int left = 0, right = (int)Stack[value].size() - 1, Answer = -1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(Stack[value][mid] <= Index) {
            Answer = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return Answer + 1;
}

int main() {
    int M; scanf("%d", &M);

    for(; M; M--) {
        int query, x; scanf("%d%d", &query, &x);

        if(query == 1) {
            insertNew(x);
        } else if(query == 2) {
            Index -= x;
        } else if(query == 3) {
            Index += x;
        } else {
            printf("%d\n", countHowMany(x));
        }
    }

    return 0;
}
