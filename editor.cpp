/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>

FILE *fin = freopen("editor.in", "r", stdin); FILE *fout = freopen("editor.out", "w", stdout);

const int MAX_LEN = 60000 + 5;

char string[MAX_LEN];

char Pair(char c) {
  if(c == '(') {
    return ')';
  }
  return ']';
}

std::vector<char > GetFinalString() {
  std::vector<char > answer;

  int size = strlen(string);

  for(int i = 0; i < size - 1; i++) {
    if(string[i] == '*') {
      if(!answer.empty()) {
        answer.pop_back();
      }
    } else {
      answer.push_back(string[i]);
    }
  }

  return answer;
}

void Check(std::vector<char > final_string) {
  std::stack<char > stk;

  for(auto& ch : final_string) {
    if(ch == '(' || ch == '[') {
      stk.push(ch);
    } else {
      if(stk.empty()) {
        printf(":(\n"); return;
      }

      if(Pair(stk.top()) == ch) {
        stk.pop();
      } else {
        printf(":(\n"); return;
      }
    }
  }

  if(!stk.empty()) {
    printf(":(\n");
  } else {
    printf(":)\n");
  }
}

int main() {
  int test_count; scanf("%d", &test_count);

  for(int i = 0; i < test_count; i++) {
    scanf("%s", string);

    auto final_string = GetFinalString();

    Check(final_string);
  }

  return 0;
}