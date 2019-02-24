#include <fstream>
using namespace std;
ifstream in("secv9.in");
ofstream out("secv9.out");
int n,i;
int main()
{
    in>>n;
    if(n<9)
        out<<"0";
    else if(n==9)
        out<<"8";
    else
    {
        out<<"72";
        for(i=10;i<n;i++)
            out<<"0";
    }
    return 0;
}
