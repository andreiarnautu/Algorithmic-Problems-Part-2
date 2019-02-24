#include <cstdio>
#include <cstdlib>

using namespace std;
FILE *fout=freopen("sub.in","w",stdout);

int main()
{
    char c;
    int x;
    printf("100\n");

        srand(69);

    for(int i = 1; i <= 100; ++i)
    {
        printf("valoareswag");
        for(int j = 1; j <= 289; ++j)
        {
            x = rand() % 25;
            c = 'a' + x;
            printf("%c", c);
        }
        printf("\n");


    }

    printf("100\n");
    for(int i = 1; i <= 100; ++i)
    {
        for(int j = 1; j <= 300; ++j)
        {
            x = rand() % 25;
            c = 'a' + x;
            printf("%c", c);
        }
        printf("\n");
    }
    return 0;
}
