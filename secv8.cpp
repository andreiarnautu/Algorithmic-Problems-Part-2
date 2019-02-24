/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

FILE *fin = freopen("secv8.in", "r", stdin); FILE *fout = freopen("secv8.out", "w", stdout);
struct Treap {
  Treap *left_son, *right_son;
  long long key, priority;
  int reversed, size;

  Treap(long long _key, long long _priority, int _reversed, int _size, Treap *_left_son, Treap *_right_son) :
    key(_key), 
    priority(_priority), 
    reversed(_reversed), 
    size(_size), 
    left_son(_left_son), 
    right_son(_right_son) {

    }
} *root, *empty_node;

void Initialize() {
  srand(time(NULL));

  root = empty_node = new Treap {0, -1, 0, 0, NULL, NULL};
}

void Update(Treap* node) {
  if(node == empty_node) return;

  node->size = node->left_son->size + node->right_son->size + 1;

  if(node->reversed) {
    std::swap(node->left_son, node->right_son);
    node->reversed ^= 1;
    node->left_son->reversed ^= 1;
    node->right_son->reversed ^= 1;
  }
}

std::pair<Treap*, Treap* > Split(Treap* node, const int position) {
  Update(node);
  if(node == empty_node) {
    return {empty_node, empty_node};
  } else if(position <= node->left_son->size) {
    auto split_left = Split(node->left_son, position);

    auto answer = std::make_pair(split_left.first, node);
    answer.second->left_son = split_left.second;
    
    Update(answer.second); 
    return answer;
  } else {
    auto split_right = Split(node->right_son, position - node->left_son->size - 1);

    auto answer = std::make_pair(node, split_right.second);
    answer.first->right_son = split_right.first;

    Update(answer.first);
    return answer;
  }
}

Treap* Join(Treap *a, Treap *b) {
  Update(a); Update(b);
  if(a == empty_node) {
    return b;
  } else if(b == empty_node) {
    return a;
  } else if(a->priority > b->priority) {
    Treap *answer = a;

    answer->right_son = Join(a->right_son, b);

    Update(answer);
    return answer;
  } else {
    Treap *answer = b;

    answer->left_son = Join(a, b->left_son);

    Update(answer);
    return answer;
  }
}

Treap *Insert(Treap* node, Treap* node_to_insert, int position) {
  Update(node);
  
  Treap *answer;

  if(node_to_insert->priority > node->priority) {
    auto split_node = Split(node, position);

    answer = node_to_insert; 
    answer->left_son = split_node.first; answer->right_son = split_node.second;
  } else if(position <= node->left_son->size) {
    answer = node;
    answer->left_son = Insert(node->left_son, node_to_insert, position);
  } else {
    answer = node;
    answer->right_son = Insert(node->right_son, node_to_insert, position - node->left_son->size - 1);
  }

  Update(answer);
  return answer;
}

Treap* NewNode(const int value) {
  return new Treap {
    value,
    ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
    0,
    1,
    empty_node,
    empty_node,
  };
}

Treap* Insert(Treap* root, int value, int position) {
  return Insert(root, NewNode(value), position);
}

Treap* Delete(Treap* node, int left, int right) {
  Update(node);
  
  auto first_split = Split(node, right); //  [1..right] + [right+1, n]
  auto second_split = Split(first_split.first, left - 1);  //  [1..left-1] + [left, right]

  return Join(second_split.first, first_split.second);
}

Treap* Reverse(Treap *node, int left, int right) {
  Update(node);

  auto first_split = Split(node, right); //  [1..right] + [right+1, n]
  auto second_split = Split(first_split.first, left - 1);  //  [1..left-1] + [left, right]

  second_split.second->reversed ^= 1;
  
  Treap *answer = Join(Join(second_split.first, second_split.second), first_split.second);
  Update(answer);
  return answer;
}

int Access(Treap* node, int position) {
  Update(node);

  if(position <= node->left_son->size) {
    return Access(node->left_son, position);
  } else if(position == node->left_son->size + 1) {
    return (int)node->key;
  } else {
    return Access(node->right_son, position - node->left_son->size - 1);
  }
}

void Print(Treap *node) {
  if(node == empty_node) return;
  Update(node);

  Print(node->left_son);
  printf("%lld ", node->key);
  Print(node->right_son);
}

void PrintTreap(Treap *node) {
  Print(node);
  printf("\n");
}

void ProcessOperations() {
  int operation_count; scanf("%d", &operation_count);
  int useless; scanf("%d ", &useless);

  for(int i = 0; i < operation_count; i++) {
    char c; scanf("%c", &c);

    if(c == 'I') {
      int position, value; scanf("%d%d ", &position, &value);
      root = Insert(root, value, position - 1);
    } else if(c == 'A') {
      int position; scanf("%d ", &position);
      printf("%d\n", Access(root, position));
    } else if(c == 'R') {
      int left, right; scanf("%d%d ", &left, &right);
      root = Reverse(root, left, right);
    } else {
      int left, right; scanf("%d%d ", &left, &right);
      root = Delete(root, left, right);
    }
  }

  PrintTreap(root);
}

int main() {
  Initialize();

  ProcessOperations();
  return 0;
}