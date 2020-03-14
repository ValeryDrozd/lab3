#include <bits/stdc++.h>
using namespace std;


///==================
///CLASS WITH NODE(TOP OF THE GRAPH)
///==================
class graphNode{
public:
    bool wall;
    int row,col,pathNumb;
    vector <int> linked;
    graphNode(){
        this->wall = 1;
        this->row = 1;
        this->col = 1;
    }
    graphNode(int col,int row,bool wall = 1){
        this->wall = wall;
        this->row = row;
        this->col = col;
        this->pathNumb = -1;
    }
    ~graphNode(){

    }
    void makeLink(int finish){
        this->linked.push_back(finish);
    }
    int distance(graphNode *to){
        return abs(to->col - this->col)+abs(to->row - this->row);
    }
};


///========================
///Class with node of queue
///========================
class queueNode
{
public:
    graphNode val;
    queueNode* next;
    queueNode();
    ~queueNode();

};



///=========================
///Class with priority queue
///=========================
class priorityQueue
{
public:
    int sz;
    queueNode *head;
    priorityQueue(){
        this->sz = 0;
        this->head = nullptr;
    }
    void pop(){
        if(this->sz==0)return;
        else{
                queueNode temp = new queueNode;
                temp = this->head;
                this->head = this->head->next;
                delete temp;
                this->sz--;
        }
    }
    void push(graphNode val,graphNode finish){
        queueNode temp = this->head;
        while(temp->next!=nullptr && val.distance(finish)>temp->next->val.distance(finish)){
            temp = temp->next;
        }
        queueNode toPush = new queueNode;
        toPush->val = val;
        toPush->next = temp->next;
        temp->next = toPush;
        this->sz++;
    }
    graphNode front(){
        return head->val;
    }
    ~priorityQueue();

};



///=====================
///CLASS WITH GRAPH
///=====================
class graph{
    int n,m,start,finish;
    graphNode* graphtops;
    vector <int> path;
    graph(){
        ifstream f;
        char filename[256];
        cout<<"Enter path to file with maze\n";
        gets(filename);
        f.open(filename);
        f>>this->n>>this->m;
        this->graphtops = new graphNode[this->n*this->m+1];
        f.ignore(256,'\n');
        string s;
        for(int i=1;i<=n;i++){
            getline(f,s);
            s = " " + s;
            for(int j=1;j<=m*2;j+=2){
                if(s[j]=='S')this->start = (i-1)*n+(j/2)+1;
                else
                if(s[j]=='F')this->finish = (i-1)*n+(j/2)+1;
                graphtops = new graphNode(i,(i-1)*n+(j/2)+1,(s[j]=='X'));
            }
        }
        f.close();
        cout<<"Read completed\n";
        for(int i=1;i<=n*m;i++){
            if(!graphtops[i].wall){
                if(i - m > 0 && !(graphtops[i-m].wall)){
                        this->graphtops[i]->linked.push_back(i-m);}
                if(i + m <= n*m && !(graphtops[i+m].wall)){
                        this->graphtops[i]->linked.push_back(i+m);}
                if((i+1)%m!=0 && i!=n*m && !(graphtops[i+1].wall)){
                        this->graphtops[i]->linked.push_back(i+1);}
                if((i+1)%m!=1 && i!=1 && !(graphtops[i-1].wall)){
                        this->graphtops[i]->linked.push_back(i-1);}
            }
        }
    }
    ~graph(){

    }

    void astar(){
        int distance[n*m+1] = {INT_MAX};

    }

    void output(){
        char filename
        remove(filename);
        ofstream f(filename);
        if(!f){cout<<"Error during reading the file\n";exit(1);}
        for(int i=1;i<=n*m;i++){
            if(this->graphtops[i].wall)f<<"X"<<"\t";
            else
            if(this->graphtops[i].pathNumb==-1)f<<" \t";
            else
                f<<this->graphtops[i].pathNumb<<'\t';
            if(i%n==0)f<<endl;
        }
        f.close();
        cout<<"Writing to the file completed\n";
    }

};

int main(){

}
