#include <set>
#include <cstdio>

using std::set;
using std::multiset;

struct Elev {
  int h;
  char nume[100];

  bool operator < (const Elev &other) const {
    return this->h < other.h;
  }

};

int main() {
  set<int> multime;

  multime.insert(7);
  multime.insert(12);
  multime.insert(3);
  multime.insert(5);
  multime.insert(5); // instructiune inutila


  multime.erase(multime.find(5)); // echivalente
  multime.erase(5);               // echivalente

  for (set<int>::iterator it = multime.begin(); it != multime.end(); ++it) {
    printf("%d\n", *it);
  }
  for (int i : multime) { // echivalente
    printf("%d\n", i);
  }

  multiset<int> multime2;
  multime2.insert(7);
  multime2.insert(12);
  multime2.insert(3);
  multime2.insert(5);
  multime2.insert(5); // 5 se insereaza de doua ori

  multime2.erase(multime2.find(5)); // sterge o singura aparitie a lui 5
  multime2.erase(5);                // sterge toate aparitiile lui 5

  for (multiset<int>::iterator it = multime2.begin(); it != multime2.end(); ++it) {
    printf("%d\n", *it);
  }
  for (int i : multime2) { // echivalente
    printf("%d\n", i);
  }

  multiset<Elev> elevi;
  elevi.insert(Elev{160, "George"});
  elevi.insert(Elev{150, "Mihai"});
  elevi.insert(Elev{150, "Maria"});
  elevi.erase(Elev{150, "Gicu"});

  for (Elev e : elevi)
    printf("%d %s\n", e.h, e.nume);

  return 0;
}
