#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 400
#define MAX_P 10'000
#define INF 1'000'000'000

// #define DEBUG_INPUT
// #define DEBUG_EK
using namespace std;

int N,P;

struct Edge{
    int target;
    int capacity;
    int flow;
    Edge * inv;
    
    Edge(int t,int c, int f, Edge * inv_): target(t), capacity(c), flow(f), inv(inv_){};
    int residual() { return capacity - flow;}
    void push(int amt){
        flow += amt;
        inv->flow -= amt;
    }
};

vector<Edge *> adj[MAX_N<<1];

// add edge from u to v
void addEdge(int u, int v, int capacity){
    
    Edge *uv = new Edge(v,capacity,0, nullptr);
    Edge *vu = new Edge(u,0,0, nullptr);
    
    // if(!isinternal){
        uv->inv = vu;
        vu->inv = uv;
    // }
    
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

const int sourcein = 0;
const int sourceout = 1;
const int sinkin = 2;
const int sinkout = 3;

int res = 0;

void max_flow(){
    int amt;
    int here;
    int next,capacity,flow;
    
    while(true){
        amt = INF;
        queue<int> q;
        vector< pair<int, Edge *> > parent(MAX_N<<1, {-1,nullptr});
        q.push(sourceout);
        parent[sourceout] = {sourceout, nullptr};
        while(!q.empty() && parent[sinkin].first == -1){
            here = q.front(); q.pop();
#ifdef DEBUG_EK
printf("here : %d \n", here);
#endif
            for(auto edge : adj[here]){
                next = edge->target;
                // if(parent[next].first != -1 || next == sourcein || next == sinkout) continue;
				if(parent[next].first != -1 ) continue;

                capacity = edge->capacity; flow = edge->flow;
                if( capacity - flow > 0){
                    q.push(next);
                    parent[next].first = here;
                    parent[next].second = edge;
                }
            }
        }
        
        if(parent[sinkin].first == -1) break;
        
        // find mat
        // here = sinkin;
        // while(here != sourceout){
        //     amt = min(amt, parent[here].second->capacity - parent[here].second->flow);
        //     here = parent[here].first;
        // }
        //amt always gonna be 1
		amt = 1;
#ifdef DEBUG_EK
        printf("amt : %d \n", amt);
#endif
        // add amt
        here = sinkin;
        while(here != sourceout){
            parent[here].second->flow += amt;
            parent[here].second->inv->flow -= amt;
            here = parent[here].first;
        }
        
        res += amt;
    }
    
}

// bool connected[MAX_N][MAX_N] = {false};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N>>P;
    int u,v;
    int uin,uout,vin,vout;
    
    // internal edge
    for(int i = 2 ; i < N; i++){
        uin = i<<1; uout = (i<<1) + 1;
        addEdge(uin, uout, 1);
    }
    
    for(int i = 0 ; i < P; i++){
        cin>>u>>v;
        u--;v--;
        // if(connected[u][v]) continue;
        if( u > v) swap(u,v);
        uin = u<<1; uout = (u<<1) + 1;
        vin = v<<1; vout = (v<<1) + 1;

        if( u == 0 ) {// source라면 sourceout만
			addEdge(uout, vin,1);
		} else if( u == 1) {// sink라면 sinkin만 고려
			addEdge(vout, uin, 1);
		} else {
		    // uout -> vin
			addEdge(uout,vin,1);

			// vout -> uin
			addEdge(vout,uin,1);
		}
    }

#ifdef DEBUG_INPUT
for(int i = 0; i < 2*N; i++){
	printf("adj[%d] : ",i);
	for(auto edge : adj[i]){
		printf("(%d, %d) ", edge->target, edge->capacity);
	}
	printf("\n");
}
#endif
    //Edmonds karp
    max_flow();
    
    cout<<res<<endl;
    return 0;
}