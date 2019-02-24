# include<fstream>
# include<deque>
using namespace std;
ifstream f("vase.in");
ofstream g("vase.out");
deque<int>v(100000);
int main()
{
    int x,n,i,s=0,j,poz,st,dr;
    char y;
    //scanf("%d",&n);
    f>>n;
    for(i = 1;i <= n;i++)
    {
        //scanf("%d",&x);
        //scanf("%c",&y);
        f>>x >> y;
        if(y=='S')
            for ( j = 0 ;j <= x - 1;j++) v.push_front(i);
        if(y == 'D')
            for ( j = 0 ;j <= x - 1;j++) v.push_back(i);
            s+=x;
    }
    g<< s / 2 << '\n';
    f>>poz;
    i = 0;
    while(v[i] != poz) i++;
    st = i;
    while(v[i] == poz) i++;
    dr = i;
    if( st <= s / 2)
        {
            g<<s / 2 - st<<" S";
        }
    else g<< st - s<<" D";

    g << '\n';

    if( dr <= s / 2)
        {
            g<<s / 2 - dr + 1<<" S";
        }
    else g<< dr - s / 2<<" D";


    return 0 ;


}
