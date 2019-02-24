/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("random.in", "r", stdin);
FILE *fout = freopen("random.out", "w", stdout);

int main() {

    int year;
    scanf("%d ", &year);
    if(year == 1982)
        printf("Robert Tarjan");
    if(year == 1986)
        printf("Leslie Valiant");
    if(year == 1990)
        printf("Alexander Razborov");
    if(year == 1994)
        printf("Avi Wigderson");
    if(year == 1998)
        printf("Peter Shor");
    if(year == 2002)
        printf("Madhu Sudan");
    if(year == 2006)
        printf("Jon Kleinberg");
    if(year == 2010)
        printf("Daniel Spielman");
    if(year == 2014)
        printf("Subhash Khot");
}
