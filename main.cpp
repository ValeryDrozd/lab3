#include <bits/stdc++.h>
using namespace std;

map <int, vector <int> > graph;
int n,m,start,fin;
vector <int> path;
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
        if(graphlist[i]!=-1){
            if(i - m > 0 && graphlist[i-m]!=-1){graph[i].push_back(i-m);}
            if(i + m <= n*m && graphlist[i+m]!=-1){graph[i].push_back(i+m);}
            if((i+1)%m!=0 && i!=n*m && graphlist[i+1]!=-1){graph[i].push_back(i+1);}
            if((i+1)%m!=1 && i!=1 && graphlist[i-1]!=-1){graph[i].push_back(i-1);}

        }
    }
    cout<<"Graph is made\n";
}


int theLeastIndex(int n,int a[]){
    int minElem = INT_MAX,minIndex = 0;
    for(int i=1;i<=n;i++){
        if(a[i]<minElem){minElem = a[i]; minIndex = i;}
    }
    return minIndex;
}

void djikstra(){
    set < pair <int,int> > st;
    st.clear();
    bool visited[n*m+1] = {false};
    int from[n*m+1] = {0};
    st.insert(make_pair(0,start));
    while(!st.empty())
    {
        auto it=st.begin();
        int v=it->second;
        visited[v]=1;
        from[v] = it->first;
        st.erase(st.begin());
        for(int i = 0;i<graph[i].size();i++){
            if(visited[graph[v][i]]==0){
                st.insert(make_pair(v,graph[v][i]));
            }
        }
    }
    cout<<"Djikstra finished\n";

    int current = fin;
    while(current!=0){
        path.push_back(current);
        current = from[current];
    }
    cout<<"Path finished\n";
    path.push_back(start);
    for(int i=0;i<path.size();i++)
        graphlist[path[i]] = i+1;
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
    djikstra();
    cout<<"Enter path to out the file\n";
    gets(filename);
    output(filename);
}
