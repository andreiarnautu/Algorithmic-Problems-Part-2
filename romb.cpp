/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("romb.in", "r", stdin);
FILE *fout = freopen("romb.out", "w", stdout);

struct Punct {
    double x, y;
    void make_point(const double x, const double y) {
        this->x = x; this->y = y;
    }
    void make_middle(const Punct p1, const Punct p2) {
        this->x = (double)(p1.x + p2.x) * 0.5;
        this->y = (double)(p1.y + p2.y) * 0.5;
    }
};

struct Dreapta {
    double a, b, c;
};

Dreapta obtineDreapta(const Punct p1, const Punct p2) {
    Dreapta d;
    d.a = p2.y - p1.y;
    d.b = p1.x - p2.x;
    d.c = p1.y * p2.x - p1.x * p2.y;
    return d;
}

int semiplan(const Dreapta d, const Punct p) {
    if(d.a * p.x + d.b * p.y + d.c > 0) {
        return 1;
    }
    return -1;
}
/*----------------------------*/
double Dx, Dy, Cx, Cy;
int k;
/*----------------------------*/
Punct Q;
long long SOL;

void readData() {
   scanf("%lf", &Dx);
   scanf("%lf", &Dy);
   scanf("%d", &k);
   scanf("%lf", &Cx);
   scanf("%lf", &Cy);
}

void Divide(Punct A, Punct B, int step) {
    if(step > k) {
        return;
    }
    Punct C; C.make_point(A.x, (double)2 * B.y - A.y);
    Punct D; D.make_point((double)2 * A.x - B.x, B.y);
    Punct Mda; Mda.make_middle(D, A);
    Punct Mab; Mab.make_middle(A, B);
    Punct Mbc; Mbc.make_middle(C, B);
    Punct Mcd; Mcd.make_middle(D, C);
    Punct O; O.make_middle(A, C);

    Dreapta D1; D1 = obtineDreapta(Mbc, Mda);
    Dreapta D2; D2 = obtineDreapta(Mcd, Mab);
    Dreapta D3; D3 = obtineDreapta(B, A);
    Dreapta D4; D4 = obtineDreapta(C, B);
    Dreapta D5; D5 = obtineDreapta(C, D);
    Dreapta D6; D6 = obtineDreapta(D, A);

    if(semiplan(D1, Q) * semiplan(D3, Q) < 1 && semiplan(D2, Q) * semiplan(D6, Q) < 1) {
        SOL = SOL * 4 - 3LL;
        Divide(A, Mab, step + 1);
    }
    else if(semiplan(D1, Q) * semiplan(D5, Q) < 1 && semiplan(D2, Q) * semiplan(D6, Q) < 1) {
        SOL = SOL * 4 - 2LL;
        Divide(Mda, O, step + 1);
    }
    else if(semiplan(D1, Q) * semiplan(D5, Q) < 1 && semiplan(D2, Q) * semiplan(D4, Q) < 1) {
        SOL = SOL * 4 - 1LL;
        Divide(O, Mbc, step + 1);
    }
    else if(semiplan(D1, Q) * semiplan(D3, Q) < 1 && semiplan(D2, Q) * semiplan(D4, Q) < 1){
        SOL = SOL * 4;
        Divide(Mab, B, step + 1);
    }
}

int main() {
    int T;
    for(scanf("%d", &T); T; T--) {
        readData();
        SOL = 1;
        Punct p1, p2;
        p1.make_point(0, Dy); p2.make_point(Dx, 0);
        Q.make_point(Cx, Cy);

        Divide(p1, p2, 1);
        printf("%lld\n", SOL);
    }
    return 0;
}
