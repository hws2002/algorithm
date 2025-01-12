#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 2'002
#define INF 1'000'000
using namespace std;

int N,M;
const int source = 0;
int sink;
int V;


// source - worker - work - sink
// 0 - 1~N - N+1~N+M - N+M+1

struct Edge{
public:
    int target, capacity, flow;
    Edge * inv;
    Edge(int t, int c, int f, Edge* inv_) : target(t), capacity(c), flow(f), inv(inv_){};
    int residual(){return capacity - flow;}
    void push(int amt){
        flow += amt;
        inv->flow -= amt;
        return ;
    }
};

vector<Edge *> adj[MAX_N];

void addEdge(int u, int v, int c){
    Edge * uv = new Edge(v,c,0,nullptr);
    Edge * vu = new Edge(u,0,0,nullptr);
    
    uv->inv = vu;
    vu->inv = uv;
    
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

int res = 0;

vector<int> from;
vector<int> level;

//Dinic bfs
bool bfs(){
    //reset
    level = vector<int> (V+1, -1);
    queue<int> q;
    int here = source;
    int next;
    q.push(here);
    level[source] = 0;
    
    while(!q.empty()){
        here = q.front(); q.pop();
        for(auto edge : adj[here]){
            next = edge->target;
            if(level[next] == -1 && edge->residual() > 0){
                q.push(next);
                level[next] = level[here]+1;
            }
        }
    }
    return level[sink] != -1;
}

//Dinic dfs
int dfs(const int src, const int dest, const int flow){
    if( src == dest) return flow;
    for(int & i = from[src]; i < adj[src].size(); i++){
        int next = adj[src][i]->target;
        if( level[next] == level[src] + 1 && adj[src][i]->residual() > 0){
            int df = dfs(next, dest, min(flow,adj[src][i]->residual()) );
            if( df > 0){
                adj[src][i]->push(df);
                return df;
            }
        }
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    int num_work, work;
    sink = N+M+1;
    V = N+M+1;
    
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
    
    //Dinic
    while(bfs()){
        //reset
        from = vector<int> (V+1, 0);
        while(true){
            int amt = dfs(source,sink, INF);
            if( amt <= 0) break;
            res += amt;
        }
    }
    
    cout<<res<<endl;
    return 0;
}
