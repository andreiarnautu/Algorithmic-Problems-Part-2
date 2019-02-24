#include <cstdio>
#include <deque>
#include <cstring>

using namespace std;

FILE *fin=freopen("secvreg.in","r",stdin);
FILE *fout=freopen("secvreg.out","w",stdout);

deque <char> d1;
deque <int> d2;

char s[100003];
int n;

inline bool open(char c)
{
    return ( c == '(' || c == '[' );
}

inline char complete(char c)
{
    if( c == '(' )
        return ')';
    if( c == ')' )
        return '(';
    if( c == '[' )
        return ']';
    if( c == ']' )
        return '[';
}

inline int last(char c)
{
    int ret;
    if( !d1.empty() && !open(c) && d1.back() == complete(c) )
    {
        ret = d2.back() + 2;
        d1.pop_back() ; d2.pop_back();
        d2[d2.size() - 1] += ret;
        return ret;
    }
    d1.push_back(c) ; d2.push_back(0);

    return 0;
}

inline int first(char c)
{
    int ret;
    if( !d1.empty() && open(c) && d1.front() == complete(c) )
    {
        ret = d2.front() + 2;
        d1.pop_front() ; d2.pop_front();
        d2[0] += ret;
        return ret;
    }
    d1.push_front(c) ; d2.push_front(0);
    return 0;
}

int main()
{
    int i, op, k;
    char c;

    gets(s);

    d2.push_back(0);

    k = strlen(s);

    for(i = 0 ; i < k ; ++i)
        last(s[i]);

    scanf("%d", &n);
    for(i = 0 ; i < n ; ++i)
    {
        scanf("%d %c", &op, &c);
        if(op)
            printf("%d\n", last(c));
        else
            printf("%d\n", first(c));
    }

    return 0;
}
