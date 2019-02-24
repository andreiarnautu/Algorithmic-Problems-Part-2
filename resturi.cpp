/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
FILE *fin = freopen("resturi.in", "r", stdin);
FILE *fout = freopen("resturi.out", "w", stdout);

const int kMaxN = 30;
const int kMaxDigits = 90;


/*-------- Structures --------*/
struct Huge {
    int size;
    int digit[kMaxDigits];

    Huge() {
        size = 1;
        for(int i = 0; i < kMaxDigits; i++) {
            this->digit[i] = 0;
        }
    }

    void SetValue(int value) {
        size = 0;
        do {
            digit[++size] = value % 10;
            value /= 10;
        }while(value != 0);
    }

    int Modulo(int value) {
        int answer = 0;
        for(int i = size; i > 0; i--) {
            answer = (answer * 10 + digit[i]) % value;
        }
        return answer;
    }

    void Multiply(int value) {
        int i, t;
        for(i = 1, t = 0; i <= size || t != 0; i++, t /= 10) {
            digit[i] = (t += digit[i] * value) % 10;
        }
        size = i - 1;
    }

    void Add(Huge &other) {
        int i, t;
        for(i = 1, t = 0; i <= this->size || i <= other.size || t != 0; i++, t /= 10) {
            this->digit[i] = (t += this->digit[i] + other.digit[i]) % 10;
        }
        this->size = i - 1;
    }

    void Write() {
        for(int i = size; i > 0; i--) {
            printf("%d", digit[i]);
        }
        printf("\n");
    }
};
/*-------- Input data --------*/
int N;
int prime[kMaxN], rest[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d%d", &prime[i], &rest[i]);
    }
}

void GetNumber() {
    Huge solution, cmmmc;
    cmmmc.SetValue(prime[0]);
    solution.SetValue(rest[0]);

    for(int i = 1; i < N; i++) {
        int r1 = solution.Modulo(prime[i]), r2 = cmmmc.Modulo(prime[i]);
        for(int j = 0; j < prime[i]; j++) {
            if((r1 + j * r2) % prime[i] == rest[i]) {
                Huge aux = cmmmc;
                aux.Multiply(j);
                solution.Add(aux);
                break;
            }
        }
        cmmmc.Multiply(prime[i]);
    }

    solution.Write();
}

int main() {
    int testCount;
    for(scanf("%d", &testCount); testCount > 0; testCount--) {
        ReadInput();
        GetNumber();
    }
    return 0;
}
