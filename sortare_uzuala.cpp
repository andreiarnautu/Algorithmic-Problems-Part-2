/**
  *  Worg
  */
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("main.in");
ofstream fout("main.out");

const int MAX_N = 1 + 100000;

int n;
int v[MAX_N];
int nr_divizori[MAX_N];

bool comp(int a, int b) {
    return nr_divizori[a] < nr_divizori[b];
}

void obtine_nr_divizori() {

}

int main() {
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> v[i];
        nr_divizori = obtine_nr_divizori(v[i]);
    }
    sort(v + 1, v + n + 1, comp);
    for(int i = 1; i <= n; i++) {
        fout << v[i] << " ";
    }

    return 0;
}
