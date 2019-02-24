/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("main.in");
ofstream cout("main.out");

const int MAX_N = 1 + 1000; //  Dimensiunea maxima a matricei

/*-------- Input data --------*/
int N, M;
int a[MAX_N][MAX_N];
/*-------- Lee --------*/
int coada_x[MAX_N * MAX_N], coada_y[MAX_N * MAX_N];  // coada_x retine coordonata x, coada_y retine coordonata y pentru fiecare element
int p, u;  // p = primul element al cozii, u = ultimul element al cozii

int dist[MAX_N][MAX_N]; // dist[i][j] = distanta minima parcursa de Romeo ca sa ajunga in casuta de coordonate i si j

int dx[] = {-1, 0, 1,  0};  // vectorii de pozitie. Parcurgand listele, ajungem pe rand in casutele de coordonate:
int dy[] = { 0, 1, 0, -1};  // (x-1, y); (x, y+1); (x+1, y); (x, y-1)
/*-------- --------*/

void ReadInput() {
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> a[i][j];
        }
    }
}

void LeeAlgorithm() {
    int xr, yr;  // coordonatele lui Romeo

    //  Initializam toate casutele ca fiind nevizitate, atribuindu-le valoarea -1
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            dist[i][j] = -1;
            if(a[i][j] == 2) {  // Daca Romeo se afla pe pozitia (i, j)
                xr = i; yr = j;
            }
        }
    }

    p = 1; u = 1;  // Coada il contine initial doar pe Romeo
    dist[xr][yr] = 0;
    coada_x[1] = xr;
    coada_y[1] = yr;

    while(p <= u) {  // Cat timp mai sunt casute de evaluat
        int x = coada_x[p];
        int y = coada_y[p];
        p++;

        for(int i = 0; i < 4; i++) {
            int vecin_x = x + dx[i];
            int vecin_y = y + dy[i];

            if(1 <= vecin_x && vecin_x <= N && 1 <= vecin_y && vecin_y <= M) {  // Verificam ca vecinul se incadreaza in matrice
                if(a[vecin_x][vecin_y] != -1 && dist[vecin_x][vecin_y] == -1) {  // Am dat peste o casuta vizitabila si neparcursa
                    // Actualizam distanta
                    dist[vecin_x][vecin_y] = dist[x][y] + 1;
                    // Introducem veciunl in coada
                    u++;
                    coada_x[u] = vecin_x;
                    coada_y[u] = vecin_y;
                }
            }
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(a[i][j] == 3) {  // Am dat peste Julieta
                cout << dist[i][j];  // Afisam distanta pana la Julieta
            }
        }
    }
}

int main() {
    ReadInput();
    LeeAlgorithm();
    WriteOutput();
    return 0;
}
