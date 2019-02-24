# include <fstream.h>
ifstream f("xy.in");
ofstream g("xy.out");
int n,m,i,j,k,r,a[101][101],jucator=1,max,s,x,y,M;

int marcheaza(int jucator, int x, int y)
{
  if(a[x][y]!=0) return 0;
  int xs,xj,ys,yd,c=1;
  if(jucator==1) // trasez un X
   { a[x][y]=1;
	 xs=x-1;xj=x+1;ys=y-1;yd=y+1;
	 while(xs>0 && xj<n+1 && ys>0 && yd<m+1 && a[xs][ys]!=2 && a[xs][yd]!=2 && a[xj][ys]!=2 && a[xj][yd]!=2)
	 { c+= (a[xs][ys]==0)+(a[xs][yd]==0)+(a[xj][ys]==0)+(a[xj][yd]==0);
	   a[xs][ys]=a[xs][yd]=a[xj][ys]=a[xj][yd]=1;
	   xs--,xj++,ys--,yd++;
	 }
   }
   else // trasez un Y
	{a[x][y]=2;
     xs=x-1;xj=x+1;ys=y-1;yd=y+1;
	 while(xs>0 && xj<n+1 && ys>0 && yd<m+1 && a[xs][ys]!=1 && a[xs][yd]!=1 && a[xj][y]!=1)
	 { c+= (a[xs][ys]==0)+(a[xs][yd]==0)+(a[xj][y]==0);
	   a[xs][ys]=a[xs][yd]=a[xj][y]=2;
	   xs--,xj++,ys--,yd++;
	 }
	}
	return c;
}

void arie()
{ int i,j,j1,j2;
   for(i=1;i<=n;i++)
	 {for(j=1;j<=m;j++)
	     if(a[i][j]!=0) a[i][j]=a[i-1][j]+1;
	   for(j=1;j<=m;j++)
	    if(a[i][j]!=0)
	       { j1=j;j2=j;
		 while(j1 && a[i][j1]>=a[i][j])j1--;
		 while(j2<=m && a[i][j2]>=a[i][j])j2++;
		 j1++;j2--;
		 if((j2-j1+1)*a[i][j]>M) M= (j2-j1+1)*a[i][j];
	       }

	 }

}

int main()
{f>>n>>m>>k;
 do
 {f>>x>>y;
  r=marcheaza(jucator,x,y);
  if(r>max)max=r;
  s=s+r;
  jucator=!jucator;
  k--;
 }while(k && r>1);

 arie();
 g<<max<<' '<<n*m-s<<' '<<M<<'\n';
 f.close();g.close();
return 0;
}
