/**
  *  Worg
  */
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
ifstream fin("showroom.in");
ofstream fout("showroom.out");

const int MAX_DEALERS = 1 + 500;
const int MOD = 9001;

/*---------------------------------*/
int N, A, R, K;
/*---------------------------------*/
string String, current;
vector <string> vec[MAX_DEALERS];
/*---------------------------------*/
unordered_map <string, int> Map;
set <int> Set;
int father[MAX_DEALERS];
int dealerCount;
/*---------------------------------*/
vector <int> dealers;
/*---------------------------------*/

void readFirst() {
    fin >> N >> A >> R >> K;
    getline(fin, String);
}

void getModels(int index) {
    int Size = (int)String.size();
    for(int i = 0; i < Size; ++i) {
        if(String[i] != ' ') {
            current.erase();
            for(; i < Size && String[i] != ' '; ++i) {
                current += String[i];
            }
            bool ok = true;
            for(int j = 0; j < (int)vec[index].size(); ++j) {
                if(current == vec[index][j]) {
                    ok = false;
                }
            }
            if(ok) {
                vec[index].push_back(current);
            }
        }
    }
}

int group(int node) {
    if(node != father[node]) {
        father[node] = group(father[node]);
    }
    return father[node];
}

void unite(int x, int y) {
    x = group(x); y = group(y);
    if(y > x) {
        father[y] = x;
    }
    else {
        father[x] = y;
    }
}

void getDealers() {
    for(int i = 1; i <= N; ++i) {
        getline(fin, String);
        getModels(i);
    }

    for(int i = 1; i <= N; ++i) {
        father[i] = i;
    }

    for(int i = 1; i <= N; ++i) {
        Set.clear();
        for(vector <string>::iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
            int dealer = Map[*it];
            if(dealer != 0) {
                Set.insert(dealer);
            }
            else {
                Map[*it] = i;
            }
        }
        Set.insert(i);
        for(set<int>::iterator it = Set.begin(); it != Set.end(); ++it) {
            unite(*Set.begin(), *it);
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(group(i) == i) {
            dealerCount++;
            dealers.push_back(i);
        }
    }
    fout << dealerCount << '\n';
}

void addStrings() {
    for(int i = 1; i <= N; ++i) {
        if(group(i) != i) {
            for(vector <string>::iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
                if(Map[*it] == i) {
                    vec[group(i)].push_back(*it);
                }
            }
        }
    }
}

int invMod(int p, bool marked) {
    int fact = 1;
    for(int i = 2; i <= p; ++i) {
        if(marked && i == MOD) {
            continue;
        }
        fact = (fact * i) % MOD;
    }

    int answer = 1;
    for(int i = 1; i <= MOD; i <<= 1) {
        if(i & (MOD - 2)) {
            answer = (answer * fact) % MOD;
        }
        fact = (fact * fact) % MOD;
    }
    return answer;
}

int comb(int p, int q) {

    int answer = 1;
    if(p - q >= q) {
        bool marked = false;
        int coef = 0;
        if(MOD <= q) {
            for(int i = 2; i * MOD <= p; ++i) {
                if(p - q <= i * MOD) {
                    marked = true;
                    coef = i;
                }
            }
        }
        for(int i = p - q + 1; i <= p; ++i) {
            if(marked && coef * MOD == i) {
                answer = (answer * coef) % MOD;
                continue;
            }
            answer = (answer * i) % MOD;
        }
        answer = (answer * invMod(q, marked)) % MOD;
    }
    else {
        bool marked = false;
        int coef = 0;
        if(MOD <= p - q) {
            for(int i = 2; i * MOD <= p; ++i) {
                if(q < i * MOD) {
                    marked ^= true;
                    coef = i;
                }
            }
        }
        for(int i = q + 1; i <= p; ++i) {
            if(marked && coef * MOD == i) {
                answer = (answer * coef) % MOD;
                continue;
            }
            answer = (answer * i) % MOD;
        }
        answer = (answer * invMod(p - q, marked)) % MOD;
    }

    return answer;
}

void countPossibilities() {
    int answer = 1, current = A;

    for(int i = 0; i < dealerCount; ++i) {
        if(current <= (int)vec[dealers[i]].size()) {
            answer = (answer * comb((int)vec[dealers[i]].size(), current)) % MOD;
        }
        current = (current + R) % K;
    }

    fout << answer << '\n';
}

int main() {
    readFirst();
    getDealers();
    addStrings();
    countPossibilities();

    return 0;
}
