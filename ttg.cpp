// Time Travel Gossip - Algoritmiada Runda Finala 2014
#include <cstdio>
#include <algorithm>
#define max( a , b ) ((a > b) ? a : b)
#define Dim 300001
using namespace std;

FILE *fin = freopen("ttg.in","r",stdin);
FILE *fout = freopen("ttg.out","w",stdout);

long long int N, M, k, nr, p1, p2;
struct gossip{long long int Max, Min;} Interval[Dim], Change[Dim];


void New_Time_Travel()
{
    long long int Lifespan, MAX, MIN;
    scanf("%lld", &Lifespan);
    scanf("%lld", &MAX);
    MIN = MAX;

    int x;
    for(long long int i = 2 ; i <= Lifespan ; ++i )
    {
        scanf("%d", &x);
        if( x < MAX )
        {
            if( x < MIN )
                MIN = x;
        }
        if( x > MAX )
        {
            if( MAX != MIN )
            {
                ++k;
                Interval[k].Max = MAX , Interval[k].Min = MIN;
            }
            MAX = MIN = x;
        }
    }

    if( MAX > MIN )
    {
        ++k;
        Interval[k].Max = MAX, Interval[k].Min = MIN;
    }
}

inline long long int comp( gossip a, gossip b )
{
    return( a.Max < b.Max );
}

void Order()
{
    p1 = k;
    p2 = k - 1;
    bool ok;
    long long int Minim = -1 , last = -1, lastmin = 10000000;

    while( p2 > 0 )
    {
        ok = 0;
        Minim = Interval[p1].Min ;
        while( Interval[p1].Min <= Interval[p2].Max )
            {
                ok = 1;
                if( Interval[p2].Max <= Interval[p1].Max )
                {
                    Interval[p2].Max = Interval[p1].Max;
                    if( Interval[p2].Min < Minim )
                        Minim = Interval[p2].Min;
                }
                --p2;
            }

        if( last == Interval[p1].Max )
        {
            if( lastmin > Minim )
                Change[nr].Min = Minim;
            lastmin = min(Minim , lastmin);
        }

        else
        {
            Change[++nr].Max = Interval[p1].Max;
            Change[nr].Min = Minim;
            last = Interval[p1].Max;
            lastmin = Minim;
        }

        --p1;

        if( p1 == p2 )
            --p2;

    }

    for(int i = p1 ; i > 0 ; --i )
    {
        if( Interval[i].Max != last )
        {
            ++nr;
            Change[nr].Max = Interval[p1].Max;
            Change[nr].Min = Interval[p1].Min;
            last = Interval[i].Max;
            lastmin = Interval[i].Min;
        }
        if( Interval[i].Max == last && Interval[i].Min < lastmin )
        {
            lastmin = Interval[i].Min;
            Change[nr].Min = Interval[i].Min;
        }
    }
}


inline int cmp(gossip a, gossip b)
{
    return( a.Min < b.Min );
}

void Solve(long long int q)
{
    long long int st, dr, m;
    st = 0;
    dr = nr + 1;

    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        if( Change[m].Min <= q )
            st = m;
        else
            dr = m;
    }
    if( Change[st + 1].Min <= q && st + 1 <= nr )
        printf("%lld\n", max ( q , Change[st + 1].Max ) );
    else
        printf("%lld\n", max ( q , Change[st].Max ) );
}

int main()
{
    scanf("%lld%lld", &M, &N);
    for(long long int i = 1 ; i <= M ; ++i )
        New_Time_Travel();

    sort( Interval + 1 , Interval + k + 1 , comp);

    Order();

    sort( Change + 1 , Change + nr + 1 , cmp);

    Change[0].Min = Change[0].Max = 0;
    long long int Query;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%lld", &Query);
        Solve( Query );
    }
    return 0;
}
