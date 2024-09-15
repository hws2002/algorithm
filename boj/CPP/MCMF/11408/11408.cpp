#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 400
#define INF 2'000'000'000
#define endl '\n'

// #define DEBUG_MCMF
using namespace std;

int N,M;

struct Edge{
    public:
    int t;
    int c, f, d;
    Edge * inv;
    Edge(): t(-1), c(0),f(0), d(0),inv(nullptr){};
    Edge(int t_, int c_, int f_, int d_): t(t_), c(c_), f(f_), d(d_){};
    
    int residual(){
        return c - f;
    }
    
    void push(const int amt){
        f += amt;
        inv->f -= amt;
    }
};

vector<Edge *> adj[(MAX_N<<1)+2];

//create edge u -> v with capacity c
void addEdge(const int u, const int v, const int c, const int dist){
    Edge * uv = new Edge(v,c,0,dist); Edge * vu =  new Edge(u,0,0,-dist);
    uv->inv = vu;
    vu->inv = uv;
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

int max_flow = 0;
int min_cost = 0;

const int src = 0;
int sink;
int V;
//spfa + edmonds karp
void mcmf(){
    V = N+M+2;
    int here, next, cost;
    int amt;
    int total_dist;
    while(true){
        //1. find shortest(cheapest) path from source to sink
        queue<int> q;
        vector<pair<int,Edge*>> parent(V,{-1,nullptr});
        vector<bool> inqueue(V,false);
        // vector<int> cntUpdated(V,0);
        vector<int> dist(V,INF);
        Edge * e;
        here = src; 
        dist[here] = 0;
        q.push(here); parent[here] = {here,nullptr}; inqueue[here] = true; 
        // cntUpdated[here]++;
        while(!q.empty()){
            here = q.front(); q.pop();
            inqueue[here] = false;
            for(auto edge : adj[here]){
                next = edge->t; cost = edge->d;
                if( edge->residual() > 0 && dist[next] > dist[here] + cost){
                    dist[next] = dist[here] + cost;
                    parent[next] = {here, edge};
                    if(!inqueue[next]){
                        q.push(next);
                        inqueue[next] = true;
                        // cntUpdated[next]++;
                        // if(cntUpdated[next] >= V){
                        //     cout<<"sth went wrong"<<endl;
                        //     break;
                        // }
                    }
                }
            }
        }
        
        if( parent[sink].first == -1 ) break;
        
        // find amt
        here = sink;
        amt = INF;
        while(here != src){
            e = parent[here].second;
            amt = min(amt, e->residual());
            here = parent[here].first;
        }
        
        //assert : amt == 1
        
        // push add cost
        here = sink;
        total_dist = 0;
        while(here != src){
            e = parent[here].second;
            e->push(amt);
            total_dist += e->d;
            here = parent[here].first;
        }
#ifdef DEBUG_MCMF
printf(" amt, total_dist : (%d , %d) \n", amt, total_dist);
#endif
        max_flow += amt;
        min_cost += total_dist;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;
    sink = N+M+1;
    
    //src to worker
    for(int worker = 1; worker <= N; worker++){
        addEdge(src,worker,1,0); // don't need to create inverse edge here
    }
    
    //worker to work
    for(int worker = 1; worker <= N; worker++){
        int num_work, work, cost;
        cin>>num_work;
        while(num_work--){
            cin>>work>>cost;
            addEdge(worker, N + work, 1, cost);
        }
    }
    
    //work to sink
    for(int work = N+1; work < N+M+1; work++){
        addEdge(work, sink, 1, 0); // don't need to create inverse edge here
    }
    
    //mcmf
    mcmf();
    
    cout<<max_flow<<endl;
    cout<<min_cost<<endl;
    return 0;
}