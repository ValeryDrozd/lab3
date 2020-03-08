#include <bits/stdc++.h>
using namespace std;

map <int, vector <int> > graph;
int n,m,start,fin;
vector <int> v;
int* graphlist;
int** maze;
void readGraph(char filename[]){
    ifstream f(filename);
    if(!f){cout<<"Error during reading file\n";exit(1);}
    f>>n>>m;
    graphlist = new int[n*m+1];
    *graphlist = {-1};
    maze = new int* [n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            maze[i] = new int[m+1];
        for(int j=1;j<=n;j++)
            maze[i][j] = 0;
    }
    for(int i=0;i<=n*m+1;i++)
        graphlist[i] = -1;
    f.ignore(256,'\n');
    string s;
    for(int i=1;i<=n;i++){
        getline(f,s);
        s = " " + s;
        for(int j=1;j<=m*2+1;j+=2){
            if(s[j]==' '){
                maze[i][j/2+1] = 1;
                graphlist[(i-1)*n+(j/2)+1] = 0;
            }
        }
    }
    f.close();
    cout<<"Read completed\n";
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
    /*djikstra();
    get_path();*/
    cout<<"Enter path to out the file\n";
    gets(filename);
    output(filename);
}
