#include<cstdio>
#include<vector>// Declararea clasei Vector-STL;
using namespace std;
vector<int> V; // Crearea unui vector de tip integer numit V;
vector<int> V1(10,5); // Crearea unui vector de tip integer V1 care va fi : 5 5 5 5 5 5 5 5 5 5
vector<int> V2(V1);// Crearea unui vector de acelasi tip ca vectorul V1(toate elementele sunt copiate);
vector<int>::iterator it; // Crearea unui iterator cu care ne vom deplasa in vectorul V;
int x,i,n;
int main()
{
    freopen("vector.in","r",stdin);
    freopen("vector.out","w",stdout);
    scanf("%d",&n);
    //Citim numarul de elemente n=10;
    //Citim elementele: 1 2 3 4 5 6 7 8 9 10;
    for (i=1; i<=n; ++i)
    {
        scanf("%d",&x);
        V.push_back(x); //Inseram elementul x la finalul vectorului;

    }

    swap(V,V1); /* swap va schimba continutul elementelor din V1 cu V2
    it=V1.begin(); // Iteratorul it va avea adresa primului element din vector V1;

29.
        printf("%d\n",*it); //Vom afisa continutul iteratorului it si anume primul element din vectorul V1

30.
        V=V1;/*Aceasta operatie va copia toate elementele V1 in V
        Astefl V va redeveni 1 2 3 4 5 6 7 8 9 10 */
        V.pop_back(); // Sterge ultimul element din vectorul V; V: 1 2 3 4 5 6 7 8 9
        V.insert(V.begin(),2,3); // La inceputul lui V vor fi introduse 5 elemente egale cu 3; V:3 3 1 2 3 4 5 6 7 8 9
        it=V.begin();
        V.erase(it); // Va sterge elementul de pe pozitia iteratorului it si anume primul element; V 3 1 2 3 4 5 6 7 8 9
        for (it=V.begin(); it!=V.end(); ++it) printf("%d ",*it); // Afisarea vectorului V;
            printf("\n");
        for (it=V1.begin(); it!=V1.end(); ++it) printf("%d ",*it);//Afisarea vectorului V1;

        return 0;

}
