/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("revsecv.in"); std::ofstream fout("revsecv.out");

/*-------- Structures --------*/
struct SA {
    std::pair<int, int > values;
    int index;

    SA() {}

    SA(int x, int y, int index) {
        this->values = {x, y}; this->index = index;
    }

    bool operator <(const SA &other) const {
        return this->values < other.values;
    }
};
/*-------- Data --------*/
std::vector<std::pair<int,int > > segtree;

std::vector<int > whiteCount, blackCount;
/*-------- --------*/

std::vector<int > GetSuffixArray(const std::string S) {
    int N = (int)S.size();

    std::vector<int > suffixId = std::vector<int >(N);
    for(int i = 0; i < N; i++) {
        suffixId[i] = S[i] - 'a';
    }

    std::vector<SA > suffix = std::vector<SA >(N);
    for(int i = 0, L = 1; i < 18; i++, L <<= 1) {
        for(int j = 0; j < N; j++) {
            suffix[j].index = j;
            suffix[j].values = {suffixId[j], j + L < N ? suffixId[j + L] : -1};
        }

        std::sort(suffix.begin(), suffix.end());

        suffixId[suffix[0].index] = 0;
        for(int i = 1; i < N; i++) {
            if(suffix[i - 1].values == suffix[i].values) {
                suffixId[suffix[i].index] = suffixId[suffix[i - 1].index];
            } else {
                suffixId[suffix[i].index] = suffixId[suffix[i - 1].index] + 1;
            }
        }
    }

    std::vector<std::pair<int, int > > a(N);
    std::vector<int > answer(N);

    for(int i = 0; i < N; i++) {
        a[i] = {suffixId[i], i};
    }
    std::sort(a.begin(), a.end());

    for(int i = 0; i < N; i++) {
        answer[i] = a[i].second;
    }
    return answer;
}

std::vector<int > GetLcp(std::string S, std::vector<int > suffArray) {
    int N = (int)S.size();

    std::vector<int > where = std::vector<int >(N);
    for(int i = 0; i < N; i++) {
        where[suffArray[i]] = i;
    }

    std::vector<int > lcp(N);
    for(int i = 0, k = 0; i < N; i++, k = (k == 0) ? 0 : k - 1) {
        if(where[i] == N - 1) {
            k = 0;
        } else {
            int j = suffArray[where[i] + 1];
            while(i + k < N && j + k < N && S[i + k] == S[j + k]) {
                k ++;
            }
        }
        lcp[where[i]] = k;
    }

    return lcp;
}

void BuildSegtree(int node, int left, int right, std::vector<int > &lcp) {
    if(left == right) {
        segtree[node] = {lcp[left], left};
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;

        BuildSegtree(leftSon, left, mid, lcp);
        BuildSegtree(rightSon, mid + 1, right, lcp);

        segtree[node] = std::min(segtree[leftSon], segtree[rightSon]);
    }
}

void ComputePartialSums(int N, std::vector<int > suffArray) {
    whiteCount = blackCount = std::vector<int >(N, 0);

    for(int i = 0; i < N; i++) {
        if(suffArray[i] < N / 2) {
            whiteCount[i] = 1; blackCount[i] = 0;
        } else {
            whiteCount[i] = 0; blackCount[i] = 1;
        }

        if(i != 0) {
            whiteCount[i] += whiteCount[i - 1]; blackCount[i] += blackCount[i - 1];
        }
    }
}

int White(int left, int right) {
    return whiteCount[right] - ((left == 0) ? 0 : whiteCount[left - 1]);
}

int Black(int left, int right) {
    return blackCount[right] - ((left == 0) ? 0 : blackCount[left - 1]);
}

std::pair<int, int > Query(int node, int left, int right, int first, int last) {
    if(first <= left && right <= last) {
        return segtree[node];
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;

        std::pair<int, int > answer = {2e5, first};
        if(first <= mid) {
            answer = std::min(answer, Query(leftSon, left, mid, first, last));
        }
        if(mid < last) {
            answer = std::min(answer, Query(rightSon, mid + 1, right, first, last));
        }

        return answer;
    }
}

long long Solve(int N, int left, int right, int prevLcp) {
    if(left >= right) return 0;

    auto rangeLcp = Query(1, 0, N - 1, left, right - 1);
    int rangeBlack = Black(left, right), rangeWhite = White(left, right);

    return 1LL * (rangeLcp.first - prevLcp) * rangeBlack * rangeWhite + Solve(N, left, rangeLcp.second, rangeLcp.first) +
                                                                        Solve(N, rangeLcp.second + 1, right, rangeLcp.first);

}

long long TotalMatches(const std::string S) {
    //  Build suffix array and lcp
    std::vector<int > suffArray = GetSuffixArray(S);
    std::vector<int > lcp = GetLcp(S, suffArray);

    //  Build segment tree on lcp array
    int N = (int)S.size();
    segtree = std::vector<std::pair<int, int > > (N << 2);
    BuildSegtree(1, 0, N - 1, lcp);
    ComputePartialSums(N, suffArray);

    return Solve(N, 0, N - 1, 0);
}

long long OverlapMatches(const std::string S) {
    std::string T;
    for(int i = 0; i < (int)S.size(); i++) {
        T += '$'; T += S[i];
    }
    T += '$';

    long long answer = 0;
    int index = -1, center = 0, N = (int)T.size();
    std::vector<int > len(N, 0);


    for(int i = 0; i < N; i++) {
        if(i <= index) {
            len[i] = std::min(len[center - (i - center)], index - i + 1);
        }
        while(i - len[i] >= 0 && i + len[i] < N && T[i - len[i]] == T[i + len[i]]) {
            len[i] ++;
        }

        answer += 1LL * (len[i] / 2) * (len[i] / 2);

        if(i + len[i] - 1 > index) {
            index = i + len[i] - 1;
            center = i;
        }
    }

    return answer;
}

int main() {
    std::string S; fin >> S;
    std::string Srev = S; std::reverse(Srev.begin(), Srev.end());

    long long answer = TotalMatches(S + '#' + Srev) - OverlapMatches(S);

    fout << answer / 2 << '\n';
    return 0;
}
