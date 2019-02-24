/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ruksak.in", "r", stdin);
FILE *fout = freopen("ruksak.out", "w", stdout);

const int MAX_G = 1 + 3000;
const int MAX_N = 1 + 300000 + 1;
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

int N, G;
pair <int,int> vec[MAX_N];
/*----------------*/
int dp[MAX_G];
int cnt[MAX_G];
int limit = 0;
bool OK[MAX_G];
/*----------------*/

bool comp(const pair<int,int> &A, const pair<int,int> &B) {
    if(A.first != B.first) {
        return A.first > B.first;
    }
    else {
        return A.second > B.second;
    }
}

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(G);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(vec[i].first); cin.getInt(vec[i].second);
    }
    sort(vec + 1, vec + N + 1);
}

void Init() {
    OK[0] = true;
}

void Update(int index) {
    int W = vec[index].first;
    int P = vec[index].second;

    cnt[W]++;
    if(!P || cnt[W] * W > G) {
        return;
    }

    for(int i = min(limit, G - W); i >= 0; --i) {
        if(OK[i]) {
            dp[i + W] = max(dp[i + W], dp[i] + P);
            OK[i + W] = true;
        }
    }
    limit += W;
}

void writeData() {
    int answer = 0;
    for(int i = 0; i <= G; ++i) {
        answer = max(answer, dp[i]);
    }
    printf("%d", answer);
}

int main() {
    readData();
    Init();
    for(int i = 1; i <= N; ++i) {
        Update(i);
    }
    writeData();
}
