/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::string;
using std::vector;

std::ifstream fin("sir2.in");
std::ofstream fout("sir2.out");

const int mod = 37781;
const int MAX_STEP = 25;
const int MAX_P = 22;  //  The total number of patterns

/*-------- Patterns --------*/
string current;
vector<string > crt_patterns, patterns;
/*-------- Input data --------*/
long long N;
/*-------- Matrix Multiplication --------*/
int mat[MAX_P][MAX_P], final_mat[MAX_P][MAX_P];
int C[MAX_P][MAX_P];
/*-------- --------*/

string GetNext(string old) {
    string next;

    for(int i = 0; i < (int)old.size(); i++) {
        if(old[i] != '3') {
            int count = 1;
            while(i + 1 < (int)old.size() && old[i] == old[i + 1]) {
                i++; count ++;
            }
            next.push_back('0' + count);
            next.push_back(old[i]);
        } else {
            next.push_back('1');
            next.push_back('3');
        }
    }

    return next;
}

vector<string > GetPatterns(string current) {
    vector<string > answer;
    string current_pattern;

    for(int i = 0; i < (int)current.size(); i++) {
        current_pattern.push_back(current[i]);
        if(current[i] == '3') {
            answer.push_back(current_pattern);
            current_pattern.clear();
        }
    }

    return answer;
}

int Find(string pattern) {
    for(int i = 0; i < (int)patterns.size(); i++) {
        if(pattern == patterns[i]) {
            return (i + 1);
        }
    }
    return 0;
}

void FindPatterns() {
    current.push_back('3');
    for(int step = 2; step < MAX_STEP; step++) {
        current = GetNext(current);
        crt_patterns = GetPatterns(current);

        for(string pattern : crt_patterns) {
            if(!Find(pattern)) {  //  Daca am dat peste un pattern nou
                patterns.push_back(pattern);
            }
        }
    }

    std::sort(patterns.begin(), patterns.end());
    /*for(string pattern : patterns) {
        fout << pattern << '\n';
    }*/

    //  Construim matricea cu coeficientii initiali
    for(int i = 0; i < MAX_P; i++) {
        crt_patterns = GetPatterns(GetNext(patterns[i]));
        for(int j = 0; j < (int)crt_patterns.size(); j++) {
            int where = Find(crt_patterns[j]) - 1;
            mat[where][i] ++;
        }
    }

}

void Multiply(int (&A)[MAX_P][MAX_P], const int (&B)[MAX_P][MAX_P]) {
    for(int i = 0; i < MAX_P; i++) {
        for(int j = 0; j < MAX_P; j++) {
            C[i][j] = 0;

            for(int k = 0; k < MAX_P; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }

    for(int i = 0; i < MAX_P; i++) {
        for(int j = 0 ; j < MAX_P; j++) {
            A[i][j] = C[i][j];
        }
    }
}

void BuildFinalMatrix() {
    //  Initializam matricea cu matricea unitate
    for(int i = 0; i < MAX_P; i++) {
        final_mat[i][i] = 1;
    }

    N--;
    while(N) {
        if(N & 1) {
            Multiply(final_mat, mat);
        }
        Multiply(mat, mat);

        N >>= 1;
    }
}

void WriteOutput() {
    int solution = 0;

    /*for(int i = 0; i < MAX_P; i++) {
        for(int j = 0; j < MAX_P; j++) {
            fout << final_mat[i][j] << " ";
        }
        fout << '\n';
    }*/

    for(int i = 0; i < MAX_P; i++) {
        solution = (solution + final_mat[i][MAX_P - 1] * (int)patterns[i].size()) % mod;
    }
    fout << solution;
}

int main() {
    FindPatterns();
    fin >> N;
    BuildFinalMatrix();
    WriteOutput();
    return 0;
}
