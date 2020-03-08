#include <bits/stdc++.h>
using namespace std;

map <int, vector <int> > graph;
int n,m;
vector <int> v;
int* graphlist;
void readGraph(char filename[]){
    ifstream f(filename);
    if(!f){cout<<"Error during reading file\n";exit(1);}
}

void djikstra(){

}

void get_path(){

}

void output(char filename[]){
    ofstream f(filename);
    if(!f){cout<<"Error during reading the file\n";exit(1);}

}

int main(){
    char filename[256];
    cout<<"Enter path to enter file\n";
    gets(filename);
    readGraph();
    djikstra();
    get_path();
    cout<<"Enter path to out the file\n";
    gets(filename);
    output(filename);
}
