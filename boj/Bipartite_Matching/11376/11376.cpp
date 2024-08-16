#include <iostream>
#include <vector>

#define MAX_N 1'000
using namespace std;

int N,M;
const int source = 0;
int sink;

vector<int> adj[MAX_N];
// source - worker - work - sink
// 0 - 1~N - N+1~N+M - N+M+1

struct Edge{
public:
    int target, capacity, flow;
    Edge * inv;
    Edge(int t, c, f, inv_) : target(t), capacity(c), flow(f), inv(inv_){};
    int residual(){return capacity - flow};
    void push(int amt){
        flow += amt;
        inv->flow -= amt;
        return ;
    }
};

void addEdge(int u, int v, int c){
    Edge * uv = Edge(v,c,0,nullptr);
    Edge * vu = Edge(u,0,0,nullptr);
    
    uv->inv = vu;
    vu->inv = uv;
    
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

int res = 0;
void maxFlow(){
    int amt;
    int here;
    while(true){
        
        
        //find amt
        // amt always 1
        amt = 1;
        
        //push
        
    }
}

int main(){
    cin>>N>>M;
    int num_work, work;
    sink = N+M+1;
    // source to worker
    for(int worker = 1; worker <= N; worker++){
        addEdge(source,worker,2);
    }
    
    // worker to work
    for(int worker = 1 ; worker <= N; worker++){
        cin>>num_work;
        while(num_work--){
            cin>>work;
            addEdge(worker, N+work,1);
        }
    }
    
    // work to sink
    for(int work = 1; work <= M; work++){
        addEdge(N+work, sink, 1);
    }
    
    //maxflow
    maxFlow();
    
    cout<<res<<endl;
    return 0;
}