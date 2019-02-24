/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

#define left_son (node << 1)
#define right_son ((node << 1) + 1)

using namespace std;
FILE *fin = freopen("rafaela.in", "r", stdin);
FILE *fout = freopen("rafaela.out", "w", stdout);

const int MAX_N = 1 + 200000;
const int root = 1;

/*-------- Input data --------*/
int N, Q;
/*-------- Heavy Path Data --------*/
struct Node;
struct Chain;

struct Node {
    int index;
    int depth, weight;
    vector< Node* > adjacent_nodes;
    Chain* chain;

    int where;
    int initial_subtree_size;
    int current_subtree_size;
    multiset< int > my_set;

    Node() {this->weight = 0; this->index = 0;}
};

struct Chain {
    Node* father;
    vector< Node* > node_list;
    vector< int > stree;
    int delay; /* pentru construirea corecta a arborelui de intervale */
    bool ok;

    Chain() {this->ok = false; stree.clear();}
};

Node graph[MAX_N];

int global_population;
/*-------- --------*/

void read_input() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].adjacent_nodes.push_back(&graph[v]);
        graph[v].adjacent_nodes.push_back(&graph[u]);
    }
    for(int i = 1; i <= N; i++) {
        graph[i].index = i;
        scanf("%d ", &graph[i].initial_subtree_size);
        global_population += graph[i].initial_subtree_size;
    }
}

void heavy_path_decomposition(Node *node, int father = 0, int crt_depth = 1) {
    node->depth = crt_depth;
    node->weight = 1;

    Node *son;
    int son_weight = 0;

    for(Node* nxt : node->adjacent_nodes) {
        if(nxt->index != father) {
            heavy_path_decomposition(nxt, node->index, crt_depth + 1);
            node->weight += nxt->weight;
            node->initial_subtree_size += nxt->initial_subtree_size;

            if(son_weight < nxt->weight) {
                son = nxt;
                son_weight = nxt->weight;
            }
        }
    }

    if(son_weight == 0) {
        /* daca nodul e frunza, ii creem un nou lant */
        node->chain = new Chain();
    } else {
        /* altfel adaugam nodul la lantul cel mai greu din subarbore */
        node->chain = son->chain;
        for(Node* nxt : node->adjacent_nodes) {
            if(nxt != son && nxt->index != father) {
                nxt->chain->father = node;
                node->my_set.insert(nxt->initial_subtree_size);
            }
        }
    }

    node->chain->node_list.push_back(node);
    node->where = (int)node->chain->node_list.size();
}

void update_chain_data() {
    graph[0].depth = 0;
    graph[1].chain->father = &graph[0];

    for(int i = 1; i <= N; i++) {
        graph[i].current_subtree_size = graph[i].initial_subtree_size;
        Chain* chain = graph[i].chain;
        if(chain->ok == false) {
            int space_needed = (int)chain->node_list.size() + 1;
            for(int j = 0; j < (int)space_needed << 3; j++) {
                chain->stree.push_back(0);
            }

            Node *node = chain->node_list.back();
            chain->delay = node->depth - 1;

            chain->ok = true;
        }
    }
}

void update_stree(vector< int > &stree, int node, int left, int right, int first, int last, int value) {
    if(first <= left && right <= last) {
        stree[node] += value;
    } else {
        int mid = (left + right) >> 1;
        if(first <= mid) {
            update_stree(stree, left_son, left, mid, first, last, value);
        }
        if(mid < last) {
            update_stree(stree, right_son, mid + 1, right, first, last, value);
        }
    }
}

void query_stree(vector< int > &stree, int node, int left, int right, int position, int &query_answer) {
    query_answer += stree[node];

    if(left == right) { return; }

    int mid = (left + right) >> 1;
    if(position <= mid) {
        query_stree(stree, left_son, left, mid, position, query_answer);
    } else {
        query_stree(stree, right_son, mid + 1, right, position, query_answer);
    }
}

void update_tree(Node *node, int value) {
    /* intai facem update pe arborele de intervale corespunzator lantului curent */
    Chain* chain = node->chain;
    update_stree(chain->stree, 1, 1, (int)chain->node_list.size(), 1, node->depth - chain->delay, value);

    Node* first = chain->node_list.back();
    Node* father = chain->father;

    if(father->index != 0) {
        father->my_set.erase(father->my_set.find(first->current_subtree_size));
        first->current_subtree_size += value;
        father->my_set.insert(first->current_subtree_size);

        update_tree(father, value);
    }
}

int query_tree(Node* node) {
    int answer = 0;

    /* ne ocupam intai de fiul de pe lantul lui node */
    Chain* chain = node->chain;
    if(node->where != 1) {
        /* inseamna ca fiul nu este capat de lant ( cu alte cuvinte nu e frunza ) */
        int pos = node->where - 2;

        Node *son = chain->node_list[pos];
        int added_in_subtree = 0;
        query_stree(chain->stree, 1, 1, (int)chain->node_list.size(), son->depth - chain->delay, added_in_subtree);

        answer = max(answer, added_in_subtree + son->initial_subtree_size);
    }

    /* apoi ne uitam la fiii ceilalti */
    if(!node->my_set.empty()) {
        multiset< int >::iterator it = node->my_set.end();
        it--;

        answer = max(answer, *it);
    }

    /* apoi ne uitam la ce se afla deasupra lui node */
    int added_in_subtree = 0;
    query_stree(chain->stree, 1, 1, (int)chain->node_list.size(), node->depth - chain->delay, added_in_subtree);

    answer = max(answer, global_population - (added_in_subtree + node->initial_subtree_size));
    return answer;
}

void process_operations() {
    for(int i = 1; i <= Q; i++) {
        char type; scanf("%c", &type);

        if(type == 'Q') {
            int id; scanf("%d ", &id);
            printf("%d\n", query_tree(&graph[id]));
        } else {
            int nr, id; scanf("%d%d ", &nr, &id);
            update_tree(&graph[id], nr);
            global_population += nr;
        }
    }
}

int main() {
    read_input();
    heavy_path_decomposition(&graph[root]);
    update_chain_data();
    process_operations();
    return 0;
}
