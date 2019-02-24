#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <vector>
#include <map>

using namespace std;

#define NMAX 260
#define INF 666666666

struct clqtree_node
{
	map<int, int> *m;
	vector<int> *v;
	vector<struct clqtree_node*> *fiu;
	int *wmax;
};

struct clqtree_node *root;
char A[NMAX][NMAX];
int w[NMAX];
map<int, int> mm[NMAX];
vector<int> vv[NMAX];
vector<struct clqtree_node*> ff[NMAX];
int out[NMAX], sel_stupid[NMAX], nvc[NMAX][NMAX]; /* nr de vecini comuni pe care ii au i si j */
int M, N, next;

int* getRandomPermutation(void)
{
	int i, j, *p;
	char *used;

	p = (int *) malloc((N + 1) * sizeof(int));
	used = (char *) malloc((N + 1) * sizeof(char));

	for (i = 1; i <= N; i++)
		used[i] = 0;

	srand(789);

	for (i = 1; i <= N; i++)
	{
		do
		{
			j = 1 + (rand() % N);
		}
		while (used[j]);

		p[i] = j;
		used[j] = 1;
	}

	free(used);
	return p;
}

int* findPEO_N4(void) // find a Perfect Elimination Ordering (in O(N^4))
{
	int *peo, *list, *v, i, j, k, l, m, size, nv;

	peo = (int *) malloc((N + 1) * sizeof(int));
	v = (int *) malloc((N + 1) * sizeof(int));

	size = N;
	list = getRandomPermutation(); // ca sa vad ce s eintampla pe cazul random

	/*
	fprintf(stderr, "random ordering =");
	for (i = 1; i <= N; i++)
		fprintf(stderr, " %d", list[i]);
	fprintf(stderr, "\n");

	fprintf(stderr, "PEO =");
	*/

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= size; j++)
		{
			nv = 0;
			for (k = 1; k <= size; k++)
				if (A[list[j]][list[k]])
					v[++nv] = list[k];

			// verifica daca vecinii lui formeaza o clica
			k = 1;

			for (l = 1; l < nv && k; l++)
				for (m = l + 1; m <= nv && k; m++)
					if (!A[v[l]][v[m]])
						k = 0;

			if (k)
				break;
		}

		if (j > size)
		{
			fprintf(stderr, "no node found at step %d : error\n", i);
			exit(0);
		}

		k = list[j];
		peo[i] = k;

		//fprintf(stderr, " %d", k);

		l = 0;
		for (j = 1; j <= size; j++)
			if (list[j] != k)
				list[++l] = list[j];

		size--;
	}

	//fprintf(stderr, "\n");

	free(list);
	free(v);

	return peo;
}

int* findPEO_N3(void) // find a Perfect Elimination Ordering (in O(N^3))
{
	int *peo, *list, *v, i, j, k, l, nv;

	peo = (int *) malloc((N + 1) * sizeof(int));
	v = (int *) malloc((N + 1) * sizeof(int));

	list = getRandomPermutation(); // ca sa vad ce s eintampla pe cazul random

	/*
	fprintf(stderr, "random ordering =");
	for (i = 1; i <= N; i++)
		fprintf(stderr, " %d", list[i]);
	fprintf(stderr, "\n");

	fprintf(stderr, "PEO =");
	*/

	// initializeaza nvc (nr de vecini comuni)
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
		{
			nvc[i][j] = 0;

			for (k = 1; k <= N; k++)
				if (A[i][k] && A[j][k])
					nvc[i][j]++;
		}

	for (i = 1; i <= N; i++)
		out[i] = 0;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
			if (!out[list[j]])
			{
				nv = 0;
				for (k = 1; k <= N; k++)
					if (!out[k] && A[list[j]][k])
						v[++nv] = k;

				// verifica daca e ok
				k = 1;
				for (l = 1; l <= nv && k; l++)
					if (nvc[list[j]][v[l]] != nv - 1)
						k = 0;

				if (k)
					break;
			}


		if (j > N)
		{
			fprintf(stderr, "no node found at step %d : error\n", i);
			exit(0);
		}

		k = list[j];
		peo[i] = k;
		out[k] = 1;

		//fprintf(stderr, " %d", k);

		// update nvc (now that k is out)
		for (j = 1; j <= N; j++)
			if (!out[j] && A[j][k])
				for (l = 1; l <= N; l++)
					if (!out[l] && A[l][k])
						nvc[j][l]--;
	}

	//fprintf(stderr, "\n");

	free(list);
	free(v);

	return peo;
}

struct clqtree_node* alloc_node(void)
{
	struct clqtree_node* node;

	node = (struct clqtree_node*) malloc(sizeof(struct clqtree_node));
	node->m = &(mm[next]);
	node->m->clear();
	node->v = &(vv[next]);
	node->v->clear();
	node->fiu = &(ff[next]);
	node->fiu->clear();

	next++;

	return node;
}

int find_parent(struct clqtree_node *parent, struct clqtree_node *son)
{
	int ok = 1, i, x, y;

	for (i = 0; ok && i < son->v->size(); i++)
	{
		x = (*(son->v))[i];

		if (!((*(parent->m))[x]))
			ok = 0;
	}

	if (ok)
	{
		parent->fiu->push_back(son);
		return ok;
	}

	for (i = 0; i < parent->fiu->size(); i++)
	{
		ok = find_parent((*(parent->fiu))[i], son);

		if (ok)
			break;
	}

	return ok;
}

struct clqtree_node* build_clqtree(int idx, int *peo)
{
	struct clqtree_node *node, *root;
	int i;

	node = alloc_node();

	for (i = idx + 1; i <= N; i++)
		if (A[peo[idx]][peo[i]])
		{
			node->v->push_back(peo[i]);
			(*(node->m))[peo[i]] = node->v->size();
		}

	if (idx < N)
	{
		root = build_clqtree(idx + 1, peo);

		// cauta un nod care sa contina in clica toti vecinii lui peo[idx]
		if (!find_parent(root, node))
		{
			fprintf(stderr, "could not find parent at step %d\n : error", idx);
			exit(0);
		}
	}

	node->v->push_back(peo[idx]);
	(*(node->m))[peo[idx]] = node->v->size();

	if (idx == N)
		return node;
	else
		return root;
}

void df_clqtree(struct clqtree_node *n)
{
	int i, j, x, y, z, extra;
	struct clqtree_node *f;

	if (n == NULL)
	{
		fprintf(stderr, "wtf?\n");
		return;
	}

	for (i = 0; i < n->fiu->size(); i++)
		df_clqtree((*(n->fiu))[i]);

	n->wmax = (int*) malloc((n->v->size() + 1) * sizeof(int));

	n->wmax[0] = 0;

	for (i = 0; i < n->v->size(); i++)
	{
		x = (*(n->v))[i];
		n->wmax[i + 1] = w[x];
	}

	// compute best_stupid

	extra = z = 0;

	for (i = 0; i < n->v->size(); i++)
	{
		x = (*(n->v))[i];
		if (n->wmax[i + 1] > extra)
			extra = n->wmax[i + 1],
			z = x;
	}

	sel_stupid[z] = 1;

	// DP

	for (i = 0; i < 1 + n->v->size(); i++)
	{
		if (i == 0)
			x = 0;
		else
			x = (*(n->v))[i - 1];

		for (j = 0; j < n->fiu->size(); j++)
		{
			extra = 0;

			f = (*(n->fiu))[j];
			y = (*(f->m))[x];

			if (y)
				extra = f->wmax[y] - w[x];
			else
			{
				for (y = 0; y < 1 + f->v->size(); y++)
				{
					if (y == 0)
						z = 0;
					else
						z = (*(f->v))[y - 1];

					if (f->wmax[y] > extra && !((*(n->m))[z]))
						extra = f->wmax[y];
				}
			}

			n->wmax[i] += extra;
		}
	}
}

int find_max_value(struct clqtree_node *n, int *tset)
{
	int x, y, oky, value;

	value = 0;

	for (x = 0; x < 1 + n->v->size(); x++)
		if (n->wmax[x] > value)
		{
			if (x == 0)
				y = 0;
			else
				y = (*(n->v))[x - 1];

			if (tset[y] == 0)
				continue;

			value = n->wmax[x];
			oky = y;
		}

	if (oky > 0)
		tset[oky] = 1;

	for (x = 0; x < n->v->size(); x++)
	{
		y = (*(n->v))[x];

		if (y != oky)
			tset[y] = 0;
	}

	for (x = 0; x < n->fiu->size(); x++)
		find_max_value((*(n->fiu))[x], tset);

	return value;
}

void read_data(void)
{
	int i, j;

	freopen("soc.in", "r", stdin);

	scanf("%d %d", &N, &M);

	for (i = 1; i <= N; i++)
		scanf("%d", &w[i]);

	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			A[i][j] = 0;

	while (M--)
	{
		scanf("%d %d", &i, &j);
		A[i][j] = A[j][i] = 1;
	}
}

void write_data(int best, int *marcat)
{
	int i, count, best_stupid;

	freopen("soc.out", "w", stdout);

	printf("%d\n", best);

	count = 0;
	for (i = 1; i <= N; i++)
		if (marcat[i] == 1)
			count++;

	printf("%d\n", count);

	for (i = 1; i <= N; i++)
		if (marcat[i] == 1)
			printf("%d ", i);

	printf("\n");

	best_stupid = 0;

	for (i = 1; i <= N; i++)
		if (sel_stupid[i])
			best_stupid += w[i];

	printf("best_stupid = %d\n", best_stupid);
}

int main()
{
	int *peo, *marcat, i, best;
	struct clqtree_node *root;

	read_data();
	peo = findPEO_N3();

	next = 0;
	root = build_clqtree(1, peo);

	memset(sel_stupid, 0, sizeof(sel_stupid));

	//fprintf(stderr, "*\n");

	df_clqtree(root);

	//fprintf(stderr, "**\n");

	marcat = (int *) malloc((N + 1) * sizeof(int));
	for (i = 0; i <= N; i++)
		marcat[i] = 2;

	best = find_max_value(root, marcat);

	//fprintf(stderr, "***\n");

	write_data(best, marcat);

	return 0;
}
