# include <fstream>
# include <cstring>
# define lmax 500001
using namespace std;

ifstream f("semne3.in");
ofstream g("semne3.out");

long long i,N,Max,Min,j,k;
char s[lmax];

int main()
{
    f>>N;
    f.get();
    f.get(s,N);
   // g<<s<<endl;
    Max=N; Min=1;
    i=0;
    while(i<N)
    {
        if (s[i]=='<')
        {
            g<<Min<<" ";
            ++Min; ++i;
        }
        else
        {
            j=i;
            while (s[j]=='>' && j<N) ++j;
            for (k=i;k<j;++k)
                {
                    g<<Max<<" ";
                    --Max;
                }
            if(i!=j)
                i=j;
            else
                i++;
        }
    }
    if (s[N-1]=='<')
        g<<Min<<'\n';
    else
        g<<Max<<'\n';
    return 0;
}
