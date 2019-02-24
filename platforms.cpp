/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxInf = 1e9;

/*-------- Structures --------*/
struct Platform {
    int first, second;
    int index;

    bool operator <(const Platform &other) const {
        return this->second < other.second;
    }
};
/*-------- Input data --------*/
int N, M;
std::vector<Platform > platforms;
std::vector<int > balls;
/*-------- Other data --------*/
std::vector<Platform > gaps;

std::vector<int > minCost;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    platforms.resize(N); balls.resize(M); minCost = std::vector<int >(N, kMaxInf);
    for(int i = 0; i < N; i++) {
        scanf("%d%d", &platforms[i].first, &platforms[i].second);
        platforms[i].index = i;
    }
    for(auto& ball : balls) {
        scanf("%d", &ball);
    }
    std::sort(balls.begin(), balls.end());
}

void MakeGaps() {
    gaps.clear();
    gaps.push_back({kMaxInf, balls[0], 0});
    for(int i = 1; i < (int)balls.size(); i++) {
        gaps.push_back({balls[i] - balls[i - 1], balls[i], 0});
    }
}

void UpdateSolutions() {
    std::vector<std::pair<int, int > > stack;
    std::sort(platforms.begin(), platforms.end()); std::sort(gaps.begin(), gaps.end());

    int i = 0, j = 0, lastBall = -kMaxInf;
    while(i < N) {
        if(j < M && gaps[j].second < platforms[i].second) {
            lastBall = gaps[j].second;
            while(!stack.empty() && stack.back().first <= gaps[j].first) {
                stack.pop_back();
            }
            stack.push_back({gaps[j].first, gaps[j].second});
            j ++;
        } else {
            if(platforms[i].first >= lastBall) {  ///  If we have no ball in range
                minCost[platforms[i].index] = 0;
            } else {
                int left = 0, right = (int)stack.size() - 1, answer = 0;
                int platformSize = platforms[i].second - platforms[i].first;
                while(left <= right) {
                    int mid = (left + right) >> 1;
                    if(stack[mid].first >= platformSize) {
                        answer = mid; left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                minCost[platforms[i].index] = std::min(minCost[platforms[i].index], platforms[i].second - stack[answer].second);
            }
            i ++;
        }
    }
}

void ChangeCoordinates() {
    int maxCoord = -kMaxInf;
    for(auto& ball : balls) {
        maxCoord = std::max(maxCoord, ball);
    }
    for(auto& platform : platforms) {
        maxCoord = std::max(maxCoord, platform.second);
    }

    for(auto &ball : balls) {
        ball = maxCoord - ball;
    }
    std::reverse(balls.begin(), balls.end());

    for(auto& platform : platforms) {
        int first = maxCoord - platform.second;
        int second = maxCoord - platform.first;

        platform.first = first; platform.second = second;
    }
}

void WriteOutput() {
    long long solution = 0;
    for(int i = 0; i < N; i++) {
        solution += minCost[i]; //printf("%d\n", minCost[i]);
    }
    printf("%lld\n", solution);
}

int main() {
    ReadInput();
    MakeGaps();
    UpdateSolutions();
    ChangeCoordinates();
    MakeGaps();
    UpdateSolutions();
    WriteOutput();
    return 0;
}
