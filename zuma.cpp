#include <fstream>
#include <cstring>
using namespace std;
ifstream in("zuma.in");
ofstream out("zuma.out");
char s[203];
int n,i,nr1,nr2,ok=1;
int main()
{
    in>>n;
    in.get();
    in.get(s,200);
    n--;
    if(s[n]==s[n-1] && s[n]==s[n+1])
    {

        while(ok)
        {

           // out<<"*";
            ok=0;
            if(s[n]==s[n-1] && s[n]==s[n+1])
                ok=1;
            else if(s[n+1]==s[n] && s[n+1]==s[n+2])
                ok=1;
            else
                break;
            for(i=n-1;i>=0;i--)
                if(s[i]!=s[i+1])
                    break;
            nr1=i;
            for(i=n+1;i<strlen(s);i++)
                if(s[i]!=s[i-1])
                    break;
            nr2=i;
            strcpy(s+nr1+1,s+nr2);
           // out<<s<<endl;
            n=nr1;
        }
    }
    out<<s<<endl;
    return 0;
}
