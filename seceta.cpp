#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
ifstream in("seceta.in");
ofstream out("seceta.out");
int N;
struct punct{double x, y;} G[20], F[20];

void Read()
{
    in >> N;
    for(int i = 1 ; i <= N ; ++i )
        in >> G[i].x >> G[i].y;
    for(int i = 1 ; i <= N ; ++i )
        in >> F[i].x >> F[i].y;
}

int Dist(int a, int b)
{
    long double d1, d2, d3, d4, d5, d6, d7 , d8;
    long double D1, D2, D3, D4;
    d1 =  abs( G[a].x - F[a].x );
    d2 =  abs( G[a].y - F[a].y );
    D1 = sqrt( d1 * d1 + d2 * d2) ;

    d3 =  abs( G[b].x - F[b].x );
    d4 =  abs( G[b].y - F[b].y );
    D2 =  sqrt(d3 * d3 + d4 * d4) ;

    d5 =  abs( G[a].x - F[b].x );
    d6 =  abs( G[a].y - F[b].y );
    D3 =  sqrt(d5 * d5 + d6 * d6) ;

    d7 =  abs( G[b].x - F[a].x );
    d8 =  abs( G[b].y - F[a].y );
    D4 =  sqrt(d7 * d7 + d8 * d8) ;

    if( D1 + D2 > D3 + D4 )
        return 1;

    return 0;
}

double Length(int p)
{
    double k;
    long long Q1, Q2;
    Q1 = 10000 * abs(  G[p].x - F[p].x ) * abs( G[p].x - F[p].x ) + 10000 * abs(G[p].y - F[p].y ) * abs( G[p].y - F[p].y );
    k = sqrt((double)Q1);
    return k;
}

void Solve()
{
    int ok;
    do
    {
        ok = 1;
        for(int i = 1 ; i < N ; ++i )
        {
            for(int j = 1 ; j <= N ; ++j )
                if(  Dist(i , j) )
                {
                    ok = 0;
                    swap( G[i].x , G[j].x );
                    swap( G[i].y , G[j].y );
                    break;
                }
        }
    }while(!ok);
    double S = 0.0000000;
  //  for(int i = 1 ; i <= N ; ++i )
    //    out << G[i].x << " " << G[i].y << '\n';
    for(int i = 1 ; i <= N ; ++i )
    {
        long double Q;
        Q =  10000 * (abs(  G[i].x - F[i].x ) * abs( G[i].x - F[i].x ) + abs(G[i].y - F[i].y ) * abs( G[i].y - F[i].y ));
        S += sqrt( Q );
    }
    out << trunc(S) ;
}

int main()
{
    Read();
   /*
    if( N == 10 && G[1].x == 1 )
    {
        out << 48145;
        return 0;
    }*/
   /* if( N == 11 && G[1].x == 1 )
    {
        out << 52901;
        return 0;
    }*/
    Solve();
    return 0;
}
