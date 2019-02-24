/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using std::unordered_map;

FILE *fin = freopen("poze.in", "r", stdin);
FILE *fout = freopen("poze.out", "w", stdout);

const int MAX_N = 1 + 300 + 1;
const long long mod_1 = 999999001;
const long long mod_2 = 999999017;
const long long mod_3 = 999999029;
const long long coef_1 = 1000000007;
const long long coef_2 = 1000000009;
const long long coef_3 = 1000000021;
const int buffer_dim = 1 + 100000;

/*-------- Input Reader --------*/
class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- --------*/


/*-------- Structures --------*/
struct Hash {
    long long r1, r2;
    Hash() {r1 = 0; r2 = 0;}
    Hash(const long long _r1, const long long _r2) {r1 = _r1; r2 = _r2;}

    void AddValue(int value) {
        r1 = (r1 * coef_1 + 1LL * value) % mod_1;
        r2 = (r2 * coef_2 + 1LL * value) % mod_2;
    }
    long long HashValue() {
        return r1 * 1e9 + r2;
    }
};
/*-------- Input data --------*/
int test_count;
int N, M, K;
int mat[MAX_N][MAX_N];
/*-------- Hashing --------*/
Hash partial[MAX_N][MAX_N];
Hash column_hash[MAX_N][MAX_N];
unordered_map<long long, int> my_map;
/*-------- --------*/

void ReadInput() {
    cin >> N; cin >> M; cin >> K;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> mat[i][j];
        }
    }
}

long long Power(long long base, long long exp, long long mod) {
    long long answer = 1, aux = base;
    for(long long i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (answer * aux) % mod;
        }
        aux = (aux * aux) % mod;
    }

    return answer;
}

void Precompute() {
    for(int j = 1; j <= M; j++) {
        partial[N + 1][j] = Hash();
        for(int i = N; i >= 1; i--) {
            partial[i][j] = partial[i + 1][j];
            partial[i][j].AddValue(mat[i][j]);
        }
    }
}

bool IsPossible(int length) {
    my_map.clear();  //  E posibil sa fi ramas nesterse date
    long long pow_1 = Power(coef_1, length, mod_1);
    long long pow_2 = Power(coef_2, length, mod_2);
    long long pow_3 = Power(coef_3, length, mod_1);
    long long pow_4 = Power(coef_3, length, mod_2);

    for(int i = 1; i + length - 1 <= N; i++) {
        for(int j = 1; j <= M; j++) {
            Hash hash_1 = partial[i][j];
            Hash hash_2 = partial[i + length][j];

            hash_1.r1 = (hash_1.r1 - hash_2.r1 * pow_1 + mod_1 * pow_1) % mod_1;
            hash_1.r2 = (hash_1.r2 - hash_2.r2 * pow_2 + mod_2 * pow_2) % mod_2;

            column_hash[i][j] = hash_1;
        }
    }

    for(int i = 1; i + length - 1 <= N; i++) {
        Hash now;
        for(int j = 1; j <= M; j++) {
            now.r1 = (now.r1 * coef_3 + column_hash[i][j].r1) % mod_1;
            now.r2 = (now.r2 * coef_3 + column_hash[i][j].r2) % mod_2;
            if(j > length) {
                now.r1 = (now.r1 - column_hash[i][j - length].r1 * pow_3 + mod_1 * pow_3) % mod_1;
                now.r2 = (now.r2 - column_hash[i][j - length].r2 * pow_4 + mod_2 * pow_4) % mod_2;
            }
            if(j >= length) {
                my_map[now.HashValue()] ++;
                if(my_map[now.HashValue()] >= K) {
                    return true;                                    /// @OK
                }
            }
        }
    }

    return false;
}

int GetMaxLength() {
    int length = 0;
    int left = 1, right = std::min(N, M);

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(IsPossible(mid)) {
            length = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return length;
}

int main() {
    cin.GetBuffer();
    for(cin >> test_count; test_count > 0; test_count--) {
        ReadInput();
        Precompute();
        printf("%d\n", GetMaxLength());
    }

    return 0;
}
