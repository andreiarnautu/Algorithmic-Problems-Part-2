//prof. Silviu Candale - 100 p
#include <fstream>
#include <iostream>

#define NN 100001
using namespace std;

int main(){
	int n,x,v[NN];
	long long int s=0, // cantitatea totala
		st, dr; //intervalul ocupat de lichidul x
	char d[NN];

	ifstream fin("vase.in");
	fin>>n;
	for(int i=1; i<=n; ++i)
		fin>>v[i]>>d[i], s+=v[i];
	fin>>x;

	//calculez nivelul la care se ajunge pana la lichidul x
	long long ss=0;
	for(int i=1; i<x; ++i)
		ss += v[i];
	ss /= 2;
	//determin intervalul initial al lichidului x
	int i=x;
	if(d[i]=='S')
		st = -ss-v[i]/2, dr = -ss + v[i]/2;
	else
		st = ss-v[i]/2, dr = ss + v[i]/2;

	for(i = x+1 ; i<=n ; ++i){
		//actualizez intervalul ocupat de lichidul x, in functie de directia curenta
		if(d[i]=='S')
			st = st+v[i]/2, dr = dr + v[i]/2;
		else
			st = st-v[i]/2, dr = dr - v[i]/2;
	}

	ofstream fout("vase.out");
	fout<<s/2<<endl;
	if(st>=0)
		fout<<dr<<" D\n"<<st<<" D\n";
	else
		if(dr<=0)
			fout<< -st <<" S\n"<< -dr <<" S\n";
		else
			fout<< -st <<" S\n"<< dr <<" D\n";

	return 0;
}
