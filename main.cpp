#include <bits/stdc++.h>
using namespace std;

class graph{

    ///==================
    ///CLASS WITH NODE(TOP OF THE GRAPH)
    ///==================
    class Node{
    public:
        bool wall;
        int row,col;
        vector <int> linked;
        Node(){
            this.wall = 1;
            this.row = 1;
            this.col = 1;
        }
        Node(int col,int row,bool wall = 1){
            this.number = number;
            this.wall = wall;
            this.row = row;
            this.col = col;
        }
        ~Node(){

        }
        void makeLink(int finish){
            this.linked.push_back(finish);
        }
        int distance(Node *to){
            return abs(to->col - this->col)+abs(to->row - this->row);
        }
    };
    ///=====================
    ///CLASS WITH GRAPH
    ///=====================
    int n,m,start,finish;
    //int* graphlist;
    Node* graphtops;
    graph(){
        ifstream f;
        char filename[256];
        cout<<"Enter path to file with maze\n";
        gets(filename);
        f.open(filename);
        f>>this.n>>this.m;
        this->graphtops = new Node[this.n*this.m+1];
        f.ignore(256,'\n');
        string s;
        for(int i=1;i<=n;i++){
            getline(f,s);
            s = " " + s;
            for(int j=1;j<=m*2;j+=2){
                if(s[j]=='S')this.start = (i-1)*n+(j/2)+1;
                else
                if(s[j]=='F')this.finish = (i-1)*n+(j/2)+1;
                graphtops = new Node(i,(i-1)*n+(j/2)+1,(s[j]=='X'));
            }
        }
        f.close();
        cout<<"Read completed\n";
        for(int i=1;i<=n*m;i++){
            if(!graphtops[i].wall){
                if(i - m > 0 && !(graphtops[i-m].wall)){
                        graphtops[i].linked.push_back(i-m);}
                if(i + m <= n*m && !(graphtops[i+m].wall)){
                        graphtops[i].linked.push_back(i+m);}
                if((i+1)%m!=0 && i!=n*m && !(graphtops[i+1].wall)){
                        graphtops[i].linked.push_back(i+1);}
                if((i+1)%m!=1 && i!=1 && !(graphtops[i-1].wall)){
                        graphtops[i].linked.push_back(i-1);}
            }
        }
    }
    ~graph(){

    }
    void output(){

    }

};

int main(){

}
