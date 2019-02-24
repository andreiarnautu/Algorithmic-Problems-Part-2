/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin);
FILE *fout = freopen("main.out", "w", stdout);

const int kMaxInf = 1e9;

/*-------- Structures --------*/
struct Triplet {
    int firstElement, ratio, length;
    bool operator <(const Triplet &other) const {
        if(this->firstElement != other.firstElement) {
            return this->firstElement < other.firstElement;
        } else {
            if(this->ratio != other.ratio) {
                return this->ratio < other.ratio;
            } else {
                return this->length < other.length;
            }
        }
    }
};
/*-------- Input data --------*/
int N;
std::vector<int > vec;
/*-------- --------*/

void ReadData() {
    scanf("%d", &N);
    vec.resize(N);
    for(auto& x : vec) {
        scanf("%d", &x);
    }
}

void SolveTest() {
    Triplet solution = {kMaxInf, kMaxInf, kMaxInf};
    std::vector<int > first(N), second(N);

    for(int i = 1; i < N && solution.firstElement == kMaxInf; i++) {
        int currentRatio = vec[i] - vec[0];
        if(currentRatio <= 0) continue;  ///  QUIT

        int firstSize = 0, secondSize = 0;
        for(auto x : vec) {
            if(x == vec[0] + currentRatio * firstSize) {
                first[firstSize ++] = x;
            } else {
                second[secondSize ++] = x;
            }
        }

        bool flag = false;
        for(int i = 1; i < secondSize; i++) {
            if(second[i] - second[i - 1] != second[1] - second[0] || second[i] - second[i - 1] <= 0) {
                flag = true; break;
            }
        }
        if(flag) { continue; }              ///  QUIT

        if(secondSize == 0) {
            solution = std::min(solution, {first[0], currentRatio, 2});
            continue;                  ///  QUIT
        }

        for(int count = std::max(firstSize - 2, 2); count <= firstSize; count++) {
            int firstSize_v2 = 0;
            int secondSize_v2 = 0;

            for(auto x : vec) {
                if(firstSize_v2 < count && x == vec[0] + currentRatio * firstSize_v2) {
                    firstSize_v2 ++;
                } else {
                    second[secondSize_v2 ++] = x;
                }
            }
            if(secondSize_v2 < 2) { continue; }

            flag = false;
            for(int i = 1; i < secondSize_v2; i++) {
                if(second[i] - second[i - 1] != second[1] - second[0] || second[i] - second[i - 1] <= 0) {
                    flag = true; break;
                }
            }

            if(flag == false) {
                solution = std::min(solution, {vec[0], currentRatio, count});
                break;                      ///  QUIT
            }
        }
    }

    if(solution.firstElement == kMaxInf) {
        printf("-1\n");
    } else {
        printf("%d %d %d\n", solution.firstElement, solution.ratio, solution.length);
    }
}

int main() {
    int test_count;
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        ReadData();
        SolveTest();
    }

    return 0;
}
