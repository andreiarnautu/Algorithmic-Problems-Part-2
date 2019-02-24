#include <fstream>
using namespace std;
ifstream in("printesa.in");
ofstream out("printesa.out");
int v[11],viz[1000],nr[100];

void ciur() //Totul e OK in interiorul acestei functii
{
    int i,j;
    for(i=4;i<=800;i+=2)
        viz[i]=1;
    for(i=3;i<=800;i+=2)
        if(viz[i]==0)
            for(j=i*2;j<=800;j+=i)
                viz[j]=1;
}

int main()
{
    int h,k,i,ok=0,p=0,nrc=3,kk;
    in>>k>>h;
    for(i=0;i<h;i++)
        in>>v[i];
    ciur();
    kk=k;
    for(i=0;i<h;i++)
        if(2==v[i])
            ok=1;
    if(ok==0)
    {
        nr[0]=2;
        --k;
        ++p;
    }
    ok=0;
    while(k)
    {
        ok=0;
        if(viz[nrc]==0)
        {   for(i=0;i<h;i++)
                if(nrc==v[i])
                    ok=1;
            if(ok==0)
            {
                nr[p]=nrc;
                --k;
                ++p;
            }
        }
        nrc+=2;
    }
    for(i=kk-1;i>=0;i--)
        out<<nr[i]<<" ";
    return 0;
}
