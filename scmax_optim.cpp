/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int MAX_N = 1 + 100000;

/*-------- Datele de intrare --------*/
int N;
int a[MAX_N];
/*-------- Datele algoritmului --------*/
int indice[MAX_N];
int indice_anterior[MAX_N];
int solutie[MAX_N];

int lungime;
/*-------- --------*/

void read_input() {
    /* citim datele de intrare */
    fin >> N;
    for(int i = 1; i <= N; i++) {
        fin >> a[i];
    }
}

int cauta_binar(int i) {
    int stanga = 1, dreapta = lungime, solutie = 0;

    while(stanga <= dreapta) {
        int mijloc = (stanga + dreapta) / 2;

        if(a[i] > a[indice[mijloc]]) {
            solutie = mijloc;
            stanga = mijloc + 1;
        } else {
            dreapta = mijloc - 1;
        }
    }

    return solutie + 1;
}

void construieste_dinamica() {
    indice[1] = 1; lungime = 1;

    for(int i = 2; i <= N; i++) {
        if(a[i] > a[indice[lungime]]) {
        /* daca elementul curent e mai mare decat ultimul element al subsirului, il putem adauga la capat */
            ++lungime;
            indice[lungime] = i;
            /* pentru reconstructia sirului trebuie sa stim ce element se afla inaintea celui curent */
            indice_anterior[i] = indice[lungime - 1];
        } else {
        /* cautam o pozitie pe care sa adaugam elementul curent ca sa optimizam sirul */
            int pozitie = cauta_binar(i);
            indice[pozitie] = i;
            indice_anterior[i] = indice[pozitie - 1];
        }
    }
}

void obtine_solutia() {
    int pozitie = lungime, i = indice[lungime];

    while(i > 0) {
        solutie[pozitie] = a[i];
        i = indice_anterior[i];
        pozitie --;
    }
}

void afiseaza_solutia() {
    fout << lungime << '\n';
    for(int i = 1; i <= lungime; i++) {
        fout << solutie[i] << " ";
    }
}

int main() {
    read_input();
    construieste_dinamica();
    obtine_solutia();
    afiseaza_solutia();
    return 0;
}
