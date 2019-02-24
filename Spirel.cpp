/**
  *  Pentru lautarul meu preferat, care se numeste Spirel
  */
#include <fstream>

using namespace std;
ifstream cin("spirel.in");
ofstream cout("spirel.out");

int main() {
    /* Sa inceapa confruntarea Shaolin */

    int maximGlobal = - 2000000000;
    int maximCurent = - 2000000000;
    /* maximele le initializez cu -2 * 10^9, fiindca numerele citite sunt intregi, nu naturale, si atunci pot aparea
       valori negative */

   int prec = -1;
   int x = -2000000000;

   while( 69 ) {
        cin >> x;
        if(x == 0) {
            /* daca x este 0, atunci afisam maximul curent, fiindca se termina sirul
               caz particular: se termina citirea de tot si sunt cele 2 zerouri finale, atunci nu afisam */
            if(prec != 0) {
                cout << maximCurent << " ";
            }
            /* de asemenea, actualizam si maximul global */
            if(maximGlobal < maximCurent) {
                maximGlobal = maximCurent;
            }
            /* reinitializam maximul curent cu valoarea mminima, fiindca incepem un nou sir */
            maximCurent = - 2000000000;
        } else {
            /* daca x nu este 0, actualizam maximul curent */
            if(x > maximCurent) {
                maximCurent = x;
            }
        }

        if(x == 0 && prec == 0) {
            /* conditia de oprire a citirii */
            break;
        }
        prec = x;
   }

   cout << maximGlobal << " ";

   return 0;
}
