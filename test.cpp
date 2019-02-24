#include <iostream>

using namespace std;

int main()
{
    int a[20],copie[20],n,n_copie,i,y=0,t,k,j;

    cout<<"n=";cin>>n;
    n_copie=n;

    cout<<"t=";cin>>t;
    cout<<"k=";cin>>k;

    for(i=0;i<n;i++) {
        cin>>a[i];
        copie[y++]=a[i];
    }
    for(i=0;i<n;i++){
        if(a[i]==k) {
            for(j=n-1;j>i;j--) {
                a[j+1]=a[j];
                //n++; -> Il cresti pe n in afara for-ului, o singura data, pentru ca lungimea sirului practic creste cu 1
            }
            n++;
            a[i + 1]=t;  //  Elementul pe care il inserezi il pui imediat dupa; Daca il pui pe pozitia j, j cand iese din for-ul de mai sus o sa fie egal cu i :)

            break;  //  Asta ca sa nu mai continui, fiindca e posibil sa mai ai si alte valori egale cu k
        }
    }

    for(i=0;i<n;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    for(i=0;i<n_copie;i++)
        cout<<copie[i]<<" ";

    return 0;
}