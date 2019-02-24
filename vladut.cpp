#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

ifstream fin("vladut.in");
ofstream fout("vladut.out");

int n;
char s[200], a[200];
char sep[] = {' ', ',', ';', '.'};


int litera(char c) {
    if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    {
        return 1;
    }
    return 0;
}

int vocala(char c)
{
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u')
    {
        return 1;
    }
    return 0;
}

int cifra(char c)
{
    if('0' <= c && c <= '9')
    {
        return 1;
    }
    return 0;
}

int main() {
    fin.getline(s, sizeof(s));

    int i, raspuns = 0, pos = -1;
    for(i = 0; i < strlen(s); i++)
    {
        if(litera(s[i]) && !vocala(s[i]))
        {
            pos = i;
            break;
        }
    }

    int vocale = 0;
    while(i < strlen(s))
    {
        if(vocala(s[i]))
        {
            vocale++;
        }
        else
        {
            raspuns = max(raspuns, vocale);
            pos = i;
            vocale = 0;
        }
        i++;
    }

    fout << raspuns;
    return 0;
}
