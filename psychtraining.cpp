/**
  *  Worg
  *  ..se facea cu heap..pacat ca nu mai e timp..
  */
#include <string>
#include <vector>
#include <fstream>

#define pb          push_back

using namespace std;
ifstream in("psychtraining.in");
ofstream out("psychtraining.out");

const int MAX_N = 1 + 500;

bool conflict[MAX_N][MAX_N];
bool team[MAX_N], hasTeam[MAX_N];

vector < int > a, b;
string match;
vector < string > sol;

int n, m;

void readData() {

    in >> n >> m;
    for(int i = 1; i <= m; ++i) {

        int x, y; in >> x >> y;
        conflict[x][y] = conflict[y][x] = true;
    }
}

bool existsConflict() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(conflict[i][j])
                return true;
    return false;
}

void constructMatch() { /* 0 = echipa 1, 1 = echipa 2 */

    for(int i = 1; i <= n; ++i)
        if(!hasTeam[i]) {

            int first = 0, second = 0;
            for(vector < int >::iterator it = a.begin(); it != a.end(); ++it)
                if(conflict[i][*it])
                    ++first;
            for(vector < int >::iterator it = b.begin(); it != b.end(); ++it)
                if(conflict[i][*it])
                    ++second;
            if(first >= second) { /* daca are mai multi rivali in prima echipa, il punem in echipa 2 */

                hasTeam[i] = true;
                team[i] = 1;
                b.pb(i);
                for(int j = i + 1; j <= n; ++j)
                    if(conflict[i][j] && !hasTeam[j]) {

                        hasTeam[j] = true;
                        team[j] = 0;
                        a.pb(j);
                    }
            }
            else {  /* altfel, il punem in echipa 1 */

                hasTeam[i] = true;
                team[i] = 0;
                a.pb(i);
                for(int j = i + 1; j <= n; ++j)
                    if(conflict[i][j] && !hasTeam[j]) {

                        hasTeam[j] = true;
                        team[j] = 1;
                        b.pb(j);
                    }
            }
        }

    for(vector < int >::iterator i = a.begin(); i != a.end(); ++i)
        for(vector < int >::iterator j = b.begin(); j != b.end(); ++j)
            conflict[*i][*j] = conflict[*j][*i] = false;

    for(int i = 1; i <= n; ++i) {

        if(team[i] == 0)
            match += 'a';
        else
            match += 'b';
    }
    sol.pb(match);

    match.clear();
    for(int i = 1; i <= n; ++i)
        hasTeam[i] = false, team[i] = 0;
}

int main() {

    readData();
    int repetari = 0;
    while(existsConflict() && repetari < 10) {

        constructMatch();
        ++repetari;
    }
    out << (int)sol.size() << '\n';
    for(int i = 0; i < (int)sol.size(); ++i) {

        out << sol[i] << '\n';
    }
    return 0;
}
