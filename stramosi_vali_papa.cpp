#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream in("stramosi.in");
ofstream out("stramosi.out");

const int N_max = 350005;
const int M_max = 400005;

int n, m, x, q, p, nr, curent;

queue <int> arbore;
vector <int> A[N_max];
vector <pair<int, int>> query[N_max];

int stiva[N_max], rez[M_max];
int it[N_max];

void DFS (int &nod)
{
    for (it[nod] = 0; it[nod] < query[nod].size(); it[nod]++)
        if (nr > query[nod][it[nod]].first)
            rez[query[nod][it[nod]].second] = stiva[nr - query[nod][it[nod]].first];

    for (it[nod] = 0; it[nod] < A[nod].size(); it[nod]++)
    {
        stiva[++nr] = A[nod][it[nod]];
        DFS(A[nod][it[nod]]);
    }

    if (nr > 0)
    nr--;
}

int main()
{
    in >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        in >> x;

        if (x == 0)
            arbore.push(i);
        else
            A[x].push_back(i);
    }

    for (int i = 1; i <= m; i++)
    {
        in >> q >> p;

        query[q].push_back(make_pair(p, i));
    }

    while (!arbore.empty())
    {
        curent = arbore.front();
        arbore.pop();
        nr = 1;
        stiva[nr] = curent;

        DFS(curent);
    }

    for (int i = 1; i <= m; i++)
        out << rez[i] << '\n';

    return 0;
}
