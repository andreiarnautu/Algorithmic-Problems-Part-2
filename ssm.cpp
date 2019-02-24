#include<fstream>
using namespace std;

int n,first,i1,i2,i,j;
int v[6000003];
int S,Smax;

int main(){

        ifstream f ("ssm.in");
        ofstream g ("ssm.out");
        f>>n;
        for (i=1; i<=n; i++)
        f>>v[i];
        S=v[1]; Smax=v[1]; i1=1; i2=1;
        if (S<0) {first=2; S=0;}
        for (i=2; i<=n; i++){

            S+=v[i];
            if (S>Smax) {i2=i; Smax=S; i1=first;}
            if (S<0) {S=0; first=i+1;}
        }
        g<<Smax<<" "<<i1<<" "<<i2;
}
