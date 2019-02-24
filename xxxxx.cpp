#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int i,cuv=0,x=0;
    char s[255], sp[] = "+-*/", sep[] = " .,";
    cin.getline(s, sizeof(s));
    for(i=0;i<strlen(s);i++)
        if(strchr(sp, s[i]))
            x++;

    char *p = strtok(s, sep);
    while(p!=NULL)
    {
        cuv++;
        p = strtok(NULL, sep);
    }
    cout << cuv << " " << x;
    return 0;
}
