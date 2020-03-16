#include <bits/stdc++.h>
using namespace std;

///==================
///CLASS WITH NODE(TOP OF THE GRAPH)
///==================
class graphNode{
public:
    bool wall;
    int row,col,pathNumb,number;
    vector <int> linked;
    graphNode(){
        this->wall = 1;
        this->row = 1;
        this->col = 1;
    }
    graphNode(int col,int row,int number,bool wall = 1){
        this->wall = wall;
        this->row = row;
        this->col = col;
        this->pathNumb = -1;
        this->number = number;
    }
    ~graphNode(){

    }
    void makeLink(int finish){
        this->linked.push_back(finish);
    }
    int distance(graphNode to){
        return abs(to.col - this->col)+abs(to.row - this->row);
    }
};


///========================
///Class with node of queue
///========================
class queueNode
{
public:
    int distance;
    graphNode val;
    queueNode* next;
    queueNode(){
    }
    ~queueNode(){
    }

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
                queueNode* temp = new queueNode;
                temp = this->head;
                this->head = this->head->next;
                delete temp;
                this->sz--;
        }
    }
    void push(graphNode val,int way,graphNode finish){
        if(this->sz==0){
            this->head = new queueNode;
            this->head->val = val;
            this->head->distance = this->head->val.distance(finish) + way;
            this->head->next = nullptr;
        }
        else{
            queueNode* temp = this->head;
            while(temp->next!=nullptr && val.distance(finish)+way>temp->next->distance){
                temp = temp->next;
            }
            queueNode* toPush = new queueNode;
            toPush->val = val;
            toPush->distance = val.distance(finish)+way;
            toPush->next = temp->next;
            temp->next = toPush;
        }

        this->sz++;
    }
    graphNode front(){
        return head->val;
    }
    ~priorityQueue(){

    }

};



///=====================
///CLASS WITH GRAPH
///=====================
class graph{
    public:
    int n,m,start,finish;
    graphNode* graphtops;
    vector <int> path;
    graph(){
        this->path.clear();
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
                if(s[j]=='S')this->start = (i-1)*m+(j/2)+1;
                else
                if(s[j]=='F')this->finish = (i-1)*m+(j/2)+1;
                this->graphtops[(i-1)*m+(j/2)+1] = graphNode(i,(j/2)+1,(i-1)*m+(j/2)+1,(s[j]=='X'));
            }
        }
        f.close();
        cout<<"Read completed\n";
        for(int i=1;i<=n*m;i++){
            if(!graphtops[i].wall){
                if(i - m > 0 && !(graphtops[i-m].wall)){
                        this->graphtops[i].linked.push_back(i-m);}
                if(i + m <= n*m && !(graphtops[i+m].wall)){
                        this->graphtops[i].linked.push_back(i+m);}
                if((i+1)%m!=0 && i!=n*m && !(graphtops[i+1].wall)){
                        this->graphtops[i].linked.push_back(i+1);}
                if((i+1)%m!=1 && i!=1 && !(graphtops[i-1].wall)){
                        this->graphtops[i].linked.push_back(i-1);}
            }
        }
        cout<<"Graph is made\n";
    }
    ~graph(){

    }

    void astar(){
        int distance[n*m+1] = {INT_MAX};
        int from[n*m+1] = {INT_MAX};
        for(int i=1;i<=n*m+1;i++){
            distance[i] = INT_MAX;
            from[i] = INT_MAX;
        }
        bool visited[n*m+1] = {false};
        priorityQueue Q;
        Q.push(this->graphtops[this->start],0,this->graphtops[this->finish]);
        distance[this->start] = 0;
        from[this->start] = -1;
        while(Q.sz>0 && from[this->finish]==INT_MAX){
            graphNode smth = Q.front();
            visited[smth.number] = 1;
            for(int i=0;i<Q.front().linked.size();
                if(distance[Q.front().linked[i]]>distance[Q.front().number]+1){
                    distance[Q.front().linked[i]] = distance[Q.front().number] + 1;
                    from[Q.front().linked[i]] = Q.front().number;
                }
                if(visited[Q.front().linked[i]]==0)Q.push(this->graphtops[Q.front().linked[i]],distance[Q.front().linked[i]],this->graphtops[this->finish]);
            }
            Q.pop();
            if(visited[this->finish]==1)break;
        }
        cout<<"Astar completed\n";
        if(visited[this->finish]){
            int current = this->finish;
            while(from[current]!=-1){
                this->path.push_back(current);
                current = from[current];
            }
            this->path.push_back(this->start);
            for(int i=this->path.size() - 1;i>=0;i--)
                this->graphtops[this->path[i]].pathNumb = this->path.size() - i;
        }



    }

    void output(){
        if(this->path.size()==0){cout<<"There is no path between start and finish top\n";return;}
        char filename[256];
        cout<<"Enter file to write path\n";
        gets(filename);
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
    graph g;
    g.astar();
    g.output();
}
