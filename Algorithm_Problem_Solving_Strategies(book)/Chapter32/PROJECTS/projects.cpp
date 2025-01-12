#include <iostream>
#include <vector>
#include <queue>
#include <limits>


#define MAX_N 100
#define MAX_M 100
#define MAX_V (MAX_N + MAX_M + 2)

#define INF 1000000
using namespace std;

int N,M,V;
int src, tgt;

struct Edge{
public:
    int f,c,t;
    Edge * inv;
    Edge(int f_, int c_, int t_, Edge * inv):
        f(f_), c(c_), t(t_),  inv(inv){};
    int residual(){
        return c-f;
    }

	void push(int amt){
		f += amt;
		inv->f -= amt;
	}
};

vector<Edge*> edges[MAX_V];

void addEdge(int u, int v, int f, int c){
    Edge* uv = new Edge(f,c,v,nullptr);
    Edge* vu = new Edge(0,c,u,nullptr);
    uv->inv = vu;
    vu->inv = uv;
    edges[u].push_back(uv);
    edges[v].push_back(vu);
}

int bidx2vidx(int bidx){
	return bidx + 1;
}

int eidx2vidx(int eidx){
	return eidx + N + 1;
}

void modelGraph(int & total_profit){
	int bprofit;
	for(int bidx = 0; bidx < N; bidx++){
		cin>>bprofit;
		addEdge(src, bidx2vidx(bidx), 0, bprofit);
		total_profit += bprofit;
	}
	
	int ecost;
	for(int eidx = 0; eidx < M; eidx++){
		cin>>ecost;
		addEdge(eidx2vidx(eidx), tgt, 0, ecost);
	}
	
	bool needed;
	for(int bidx = 0; bidx < N; bidx++){
		for(int eidx = 0; eidx < M; eidx++){
			cin>>needed;
			if(needed)
				addEdge(bidx2vidx(bidx),eidx2vidx(eidx),0,INF);
		}
	}
}

int Ford_Fulkerson(int src, int tgt){
    int ret = 0; 
    while (true){
        int amt = numeric_limits<int>::max(); // INT_MAX
        queue<int> q;
        vector<pair<int,int>> parent(V,{-1,-1}); // node,index
        q.push(src);
        parent[src] = {src,-1};
        while ( !q.empty() && parent[tgt].first == -1){
            int h = q.front(); q.pop();
            for(int i = 0; i < edges[h].size(); i++){
				auto & e = edges[h][i];
                if ( parent[e->t].first == -1 && e->residual() > 0){
                    parent[e->t] = {h,i};
                    q.push(e->t);
                }
            }
        }
        
        // sink에 도달하지 못했다면
        if( parent[tgt].first == -1) break;
        
        //find amt
        int h = tgt;
        while( parent[h].first != h){
            amt = min(amt, edges[ parent[h].first][parent[h].second]->residual() );
            h = parent[h].second;
        }
        
        //push amt
        h = tgt;
        while( parent[h].first != h){
			edges[parent[h].first][parent[h].second]->push(amt);
			h = parent[h].first;
        }
        ret += amt;
    }
    
    return ret;
}

void solve(){
	cin>>N>>M;
	src = 0; tgt = N+M+1;
	V = N+M+2;
	for(int i = 0; i < V; i++){
		edges[i].clear();
	}
	//modeling graph
	int total_profit = 0;
	modelGraph(total_profit);
	cout<<total_profit - Ford_Fulkerson(src, tgt)<<endl;
}

int main(){
	int C; cin>>C; while(C--) solve();
}