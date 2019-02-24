/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("xmoto.in", "r", stdin);
FILE *fout = freopen("xmoto.out", "w", stdout);

const int MAX_N = 1 + 50500;

struct Penta {
    double a, b, k, q, v;

    Penta() {this->a = this->b = this->k = this->q = this->v = 0;}

    bool operator <(const Penta &other) const {
        return this->v < other.v;
    }
};

/*-------------------*/
int N;
double L;
Penta Params[MAX_N];
/*-------------------*/
Penta Sum[MAX_N];
/*-------------------*/
vector< double > Solution;
/*-------------------*/

void readInput() {
    scanf("%d%lf", &N, &L);
    for(int i = 1; i <= N; i++) {
        scanf("%lf%lf%lf%lf%lf", &Params[i].a, &Params[i].b, &Params[i].k, &Params[i].q, &Params[i].v);
    }
    sort(Params + 1, Params + N + 1);
}

void getPartialSums() {
    Sum[1] = Params[1];
    for(int i = 2; i <= N; i++) {
        Sum[i].a = Sum[i - 1].a + Params[i].a;
        Sum[i].b = Sum[i - 1].b + Params[i].b;
        Sum[i].k = Sum[i - 1].k + Params[i].k;
        Sum[i].q = Sum[i - 1].q + Params[i].q;
    }
}

void getAnswers() {
    /* we check for v <= v[1] */
    double X = Sum[N].a;
    double Y = Sum[N].k;
    double Needed;

    if(X != 0) {
        Needed = (L - Y) / X;
        if(Needed <= Params[1].v && Needed > 0) {
            Solution.push_back(Needed);
        }
    }

    for(int i = 2; i <= N; i++) {
        X = (Sum[N].a - Sum[i - 1].a) + (Sum[i - 1].b);
        Y = (Sum[N].k - Sum[i - 1].k) + (Sum[i - 1].q);

        if(X == 0) {
            continue;
        }
        Needed = (L - Y) / X;

        if(Needed > Params[i - 1].v && Needed <= Params[i].v) {
            Solution.push_back(Needed);
        }
    }

    /* check for v >= v[N] */
    X = Sum[N].b;
    Y = Sum[N].q;
    if(X == 0) {
        return;
    }
    Needed = (L - Y) / X;

    if(Needed > Params[N].v && Needed <= 10000) {
        Solution.push_back(Needed);
    }
}

void writeOutput() {
    printf("%d\n", (int)Solution.size());
    for(vector< double >::iterator it = Solution.begin(); it != Solution.end(); it++) {
        printf("%.8f\n", *it);
    }
}

int main() {
    readInput();
    getPartialSums();
    getAnswers();
    writeOutput();
    return 0;
}
