#include <bits/stdc++.h>
using namespace std;

map <int, vector <int> > graph;
int n,m,start,fin,start,fin;
vector <int> v;
int* graphlist;
void readGraph(char filename[]){
    ifstream f(filename);
    if(!f){cout<<"Error during reading file\n";exit(1);}
    f>>n>>m;
    graphlist = new int[n*m+1];
    *graphlist = {-1};
    for(int i=0;i<=n*m+1;i++)
        graphlist[i] = -1;
    f.ignore(256,'\n');
    string s;
    for(int i=1;i<=n;i++){
        getline(f,s);
        s = " " + s;
        for(int j=1;j<=m*2+1;j+=2){
            if(s[j]!='X'){
                graphlist[(i-1)*n+(j/2)+1] = 0;
                if(s[j] == 'F')fin = (i-1)*n+(j/2)+1;
                else
                    if(s[j] == 'S')start = (i-1)*n+(j/2)+1;
            }
        }
    }
    f.close();
    cout<<"Read completed\n";
}

void makeGraph(){
    for(int i=1;i<=n*m;i++){
        if(a[i]!=-1){
            if(i - m > 0 && a[i-m]!=-1){graph[i].push_back(i-m);}
            if(i + m <= n*m && a[i+m]!=-1){graph[i].push_back(i+m);}
            if((i+1)%m!=0 && i!=n*m && a[i+1]!=-1){graph[i].push_back(i+1);}
            if((i+1)%m!=1 && i!=1 && a[i-1]!=-1){graph[i].push_back(i-1);}

        }
    }
    cout<<"Graph is made\n";
}

void djikstra(){

}

void get_path(){

}

void output(char filename[]){
    ofstream f(filename);
    if(!f){cout<<"Error during reading the file\n";exit(1);}
    for(int i=1;i<=n*m;i++){
        if(graphlist[i]==-1)f<<"X ";
        else
        if(graphlist[i]==0)f<<"  ";
        else
            f<<graphlist[i]<<' ';
        if(i%n==0)f<<endl;
    }
    f.close();
    cout<<"Writing to the file completed\n";
}
///
int main(){
    char filename[256];
    cout<<"Enter path to enter file\n";
    gets(filename);
    readGraph(filename);
    makeGraph();
    /*djikstra();
    get_path();*/
    cout<<"Enter path to out the file\n";
    gets(filename);
    output(filename);
}
