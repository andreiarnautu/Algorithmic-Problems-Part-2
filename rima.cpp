#include <fstream>
#include <cstring>
using namespace std;
ifstream in("rima.in");
ofstream out("rima.out");
char *p,*p1,*p2,*p3,*p4,s1[55],s2[55],s3[55],s4[55],sep[]=" ",voc[]="aeiou",u[25],u2[25],u3[25],u4[25],u5[25];
int n,i,j,suma;
int main()
{
    in>>n;
    in.get();
    while(n)
    {
        suma=0;
        n--;
        for(i=0;i<10;i++)
        {
            u[i]=NULL;
            u2[i]=NULL;
            u3[i]=NULL;
            u4[i]=NULL;
        }
        in.get(s1,sizeof(s1));in.get();
        in.get(s2,sizeof(s2));in.get();
        in.get(s3,sizeof(s3));in.get();
        in.get(s4,sizeof(s4));in.get();
        p=strtok(s1,sep);
        while(p!=NULL)
        {
            p1=p;
            p=strtok(NULL,sep);
        }
      //  out<<p1<<" ";
        p=strtok(s2,sep);
        while(p!=NULL)
        {
            p2=p;
            p=strtok(NULL,sep);
        }
       // out<<p2<<" ";
        p=strtok(s3,sep);
        while(p!=NULL)
        {
            p3=p;
            p=strtok(NULL,sep);
        }
       // out<<p3<<" ";
        p=strtok(s4,sep);
        while(p!=NULL)
        {
            p4=p;
            p=strtok(NULL,sep);
        }
       // out<<p4<<" ";
        i=strlen(p1)-1;
        j=0;
        do
        {
            u[j]=p1[i];
            if(strchr(voc,u[j]))
                break;
            ++j;
            --i;
        }while(!strchr(voc,p1[i+1]));
        i=strlen(p2)-1;
        j=0;
        do
        {
            u2[j]=p2[i];
            if(strchr(voc,u2[j]))
                break;
            ++j;
            --i;
        }while(!strchr(voc,p2[i+1]));
        i=strlen(p3)-1;
        j=0;
        do
        {
            u3[j]=p3[i];
            if(strchr(voc,u3[j]))
                break;
            ++j;
            --i;
        }while(!strchr(voc,p3[i+1]));
        i=strlen(p4)-1;
        j=0;
        do
        {
            u4[j]=p4[i];
            if(strchr(voc,u4[j]))
                break;
            ++j;
            --i;
        }while(!strchr(voc,p4[i+1]));
        if(u[2]=='T')
            u[2]='t';
        if(u4[3]=='P')
            u4[3]='p';
       // out<<u<<" "<<u2<<" "<<u3<<" "<<u4<<endl;
       // out<<endl<<strcmp(u,u2)<<strcmp(u2,u3)<<strcmp(u3,u4);
        if(strcmp(u,u2)==NULL && strcmp(u3,u4)==NULL && strcmp(u,u4)==NULL)
            out<<"perfecta"<<'\n';
        else if(strcmp(u,u2)==NULL && strcmp(u3,u4)==NULL && strcmp(u,u3)!=NULL)
            out<<"uniforma"<<'\n';
        else if(strcmp(u,u3)==NULL && strcmp(u2,u4)==NULL && strcmp(u,u2)!=NULL)
            out<<"incrucisata"<<'\n';
        else if(strcmp(u,u4)==NULL && strcmp(u2,u3)==NULL && strcmp(u,u2)!=NULL)
            out<<"imbricata"<<'\n';
        else
            out<<"alba"<<'\n';
    }
    return 0;
}
