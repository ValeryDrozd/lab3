#include <bits/stdc++.h>
using namespace std;

///==================
///CLASS WITH NODE(TOP OF THE GRAPH)
///==================
class graphNode{
public:
    bool wall;
    int row,col,number;
    vector <pair <int,int> > linked;
    graphNode(){
        this->wall = 1;
        this->row = 1;
        this->col = 1;
    }
    graphNode(int col,int row,int number,bool wall = 1){
        this->wall = wall;
        this->row = row;
        this->col = col;
        this->number = number;
    }
    ~graphNode(){

    }

    int distance(graphNode to){
        return abs(to.col - this->col)+abs(to.row - this->row);
    }
};




///========================
///STRUCT with node of queue
///========================
struct queueNode{
    int distance;
    graphNode val;
    queueNode* next;
};


///=========================
///Class with priority queue
///=========================
class priorityQueue
{   int sz;
    queueNode *head;
public:
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
    int size(){
        return this->sz;
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
    int n,m,start,finish;
    public:
    graphNode* graphtops;
    vector <int> path;
    graph(){
        path.clear();
        ifstream f;
        char filename[256];
        cout<<"Enter path to file with maze\n";
        gets(filename);
        f.open(filename);
        if(!f){cout<<"Error during reading the file\n";exit(1);}
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
                if(i-m>0){
                    if(!(graphtops[i-m].wall))this->graphtops[i].linked.push_back({i-m,1});
                    else{
                        if(i-2*m>0 && !(graphtops[i-2*m].wall)){
                            this->graphtops[i].linked.push_back({i-2*m,3});
                        }
                    }
                }
                if(i+m<=n*m){
                    if(!(graphtops[i+m].wall))this->graphtops[i].linked.push_back({i+m,1});
                    else{
                        if(i+2*m<=n*m && !(graphtops[i+2*m].wall)){
                            this->graphtops[i].linked.push_back({i+2*m,3});
                        }
                    }
                }
                if(i%m!=0 && i!=n*m){
                    if(!(graphtops[i+1].wall))this->graphtops[i].linked.push_back({i+1,1});
                    else{
                        if((i+2)%m!=1 && i+2<=n*m && !(graphtops[i+2].wall)){
                            this->graphtops[i].linked.push_back({i+2,3});
                        }
                    }
                }
                if(i%m!=1 && i!=1){
                    if(!(graphtops[i-1].wall))this->graphtops[i].linked.push_back({i-1,1});
                    else{
                        if((i-2)%m!=0 && !(graphtops[i-2].wall)){
                            this->graphtops[i].linked.push_back({i-2,3});
                        }
                    }
                }
               /* if(i - m > 0 && !(graphtops[i-m].wall)){
                        this->graphtops[i].linked.push_back(i-m,1);}
                if(i + m <= n*m && !(graphtops[i+m].wall)){
                        this->graphtops[i].linked.push_back(i+m,1);}
                if((i+1)%m!=0 && i!=n*m && !(graphtops[i+1].wall)){
                        this->graphtops[i].linked.push_back(i+1,1);}
                if((i+1)%m!=1 && i!=1 && !(graphtops[i-1].wall)){
                        this->graphtops[i].linked.push_back(i-1,1);}
                if()
                */
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
        while(Q.size()>0 && !visited[this->finish]){
            graphNode smth = Q.front();
            visited[smth.number] = 1;
            for(int i=0;i<Q.front().linked.size();i++){
                if(distance[Q.front().linked[i].first]>distance[Q.front().number]+Q.front().linked[i].second){
                    distance[Q.front().linked[i].first] = distance[Q.front().number] + Q.front().linked[i].second;
                    from[Q.front().linked[i].first] = Q.front().number;
                }
                if(visited[Q.front().linked[i].first]==0)Q.push(this->graphtops[Q.front().linked[i].first],distance[Q.front().linked[i].first],this->graphtops[this->finish]);
            }
            Q.pop();
        }
        cout<<"Astar completed\n";
        if(visited[this->finish]){
            int current = this->finish;
            while(from[current]!=-1){
                if((max(from[current],current) - min(from[current],current) == m) || (max(from[current],current) - min(from[current],current) == 1)){
                    this->path.push_back(current);
                    current = from[current];
                }
                else{
                    if((from[current] - current)==2){ this->path.push_back(from[current]-1);}
                    else
                    if((from[current] - current)==-2){this->path.push_back(from[current]+1);}
                    else
                    if((from[current] - current)==2*m){ this->path.push_back(from[current]-(this->m));}
                    else
                    if((from[current] - current)==-2*m){this->path.push_back(from[current]+(this->m));}
                    /*
                    switch((from[current] - current)){
                case(2):

                    break;
                case(-2):

                    break;
                case(2*this->m):

                    break;
                case(-2*this->m):

                    break;
                 //this->path.push_back(from[current]+1);
                }*/
                    this->path.push_back(current);
                    current = from[current];
                }
            }
            this->path.push_back(this->start);
        }
    }

    void output(){
        if(this->path.size()==0){cout<<"There is no way from start to finish top\n";return;}
        char filename[256];
        cout<<"Enter file to write path\n";
        gets(filename);
        remove(filename);
        ofstream f(filename);
        if(!f){cout<<"Error during reading the file\n";exit(1);}
        for(int i=1;i<=n*m;i++){
            if(i==this->start)f<<"S ";
            else
            if(i==this->finish)f<<"F ";
            else
            if(count(this->path.begin(),this->path.end(),i)==1)f<<"* ";
            else
            if(this->graphtops[i].wall)f<<"X ";
            else
            f<<"  ";
            if(i%m==0)f<<endl;
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
