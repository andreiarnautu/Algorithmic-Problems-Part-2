/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("popandai2.in", "r", stdin);
FILE *fout = freopen("popandai2.out", "w", stdout);

const int MAX_N = 1 + 1000;

/*------------------------------*/
pair< int,int > Points[MAX_N];
int N;
/*------------------------------*/
int up[MAX_N], down[MAX_N];
double SOL = 0;
/*------------------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        scanf("%d%d", &Points[i].first, &Points[i].second);
    }
}

int area(int x, int y, int z) {
    return abs(Points[x].first * (Points[z].second - Points[y].second) +
               Points[y].first * (Points[x].second - Points[z].second) +
               Points[z].first * (Points[y].second - Points[x].second));
}

void Go(int firstIndex) {
    for(int i = 1; i <= N; ++i) {
        up[i] = down[i] = 0;
    }

    for(int secondIndex = firstIndex - 2, thirdIndex = firstIndex - 1; secondIndex != firstIndex + 1; secondIndex--) {
        if(secondIndex < 1) {
            secondIndex += N;
        }
        if(thirdIndex < 1) {
            thirdIndex += N;
        }

        int AREA_1 = area(firstIndex, secondIndex, thirdIndex);
        int AREA_2;
        if(thirdIndex - 1 < 1) {
            AREA_2 = area(firstIndex, secondIndex, thirdIndex - 1 + N);
        } else {
            AREA_2 = area(firstIndex, secondIndex, thirdIndex - 1);
        }

        if(AREA_2 >= AREA_1) {
            thirdIndex--;
            if(thirdIndex < 1) {
                thirdIndex += N;
            }
        }

        up[secondIndex] = max(AREA_1, AREA_2);
    }

    for(int secondIndex = firstIndex + 2, thirdIndex = firstIndex + 1; secondIndex != firstIndex - 2 && secondIndex != firstIndex - 2 + N; secondIndex++) {
        if(secondIndex > N) {
            secondIndex -= N;
        }
        if(thirdIndex > N) {
            thirdIndex -= N;
        }

        int AREA_1 = area(firstIndex, secondIndex, thirdIndex);
        int AREA_2;
        if(thirdIndex + 1 > N) {
            AREA_2 = area(firstIndex, secondIndex, thirdIndex + 1 - N);
        } else {
            AREA_2 = area(firstIndex, secondIndex, thirdIndex + 1);
        }

        if(AREA_2 >= AREA_1) {
            thirdIndex++;
            if(thirdIndex > N) {
                thirdIndex -= N;
            }
        }

        down[secondIndex] = max(AREA_1, AREA_2);
    }

    for(int i = 1; i <= N; ++i) {
        SOL = max(SOL, (double)0.5 * (up[i] + down[i]));
    }
}

int main() {
    readData();
    for(int i = 1; i <= N - 2; i++) {
        Go(i);
    }
    printf("%.1f", SOL);
    return 0;
}
