//edmonds karp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define MAX_N 100
// #define DEBUG_INPUT
// #define DEBUG_EK
using namespace std;


int N,M;

const int source = 0;
int sink;
int V;

struct edge{
public:
    int f,c,t;
    edge * inv;
    edge() : f(0), c(0), t(-1){};
    edge(int t_, int c_):
        f(0), c(c_), t(t_), inv(nullptr){};
    int residual(){
        return c - f;
    }
};

vector<edge * > edges[MAX_N*2+2];

void addEdge(int u, int v, int c){
    edge * uv = new edge(v, c);
    edge * vu = new edge(u, 0);
    uv->inv = vu;
    vu->inv = uv;
    edges[u].push_back(uv);
    edges[v].push_back(vu);
}

int max_flow = 0;

// vector<int> sidx;

// void dinic(){
    
//     while(dinic_bfs()){
//         sidx.resize(V,0);
//         auto amt_pay = dinic_dfs(source, numeric_limits<int>::max());
//         if(amt_pay.first == 0) break;
//         min_cost += amt_pay.second;
//     }
// }

void mcmf(){
    
    while(true){
		//find path
		queue<int> q;
		vector<pair<edge*,int>> parent(V,{nullptr,-1});
		int here = source;
		q.push(here);
		parent[here] = {nullptr,here};
		while( !q.empty() && parent[sink].second == -1){
			here = q.front(); q.pop();
			for(auto ep : edges[here]){
				int next = ep->t;
				if( parent[next].second == -1 && ep->residual() > 0){
					parent[next] = {ep,here};
					q.push(next);
				}
			}
		}

		if(parent[sink].second == -1) break;

		//find amt
		int amt = numeric_limits<int>::max();
		here = sink;
		while( here != source){
			amt = min(amt, parent[here].first->residual());
			here = parent[here].second;
		}

		//push
		int single_cost = 0;
		here = sink;
#ifdef DEBUG_EK
printf("tracking here : ");
#endif
		while( here != source){
#ifdef DEBUG_EK
if( here > M) 
	printf("%d ", here-M);
else
	printf("%d ", here);
#endif
			parent[here].first->f += amt;
			parent[here].first->inv->f -= amt;
			here = parent[here].second;
		}
#ifdef DEBUG_EK
		printf("amt : %d \n",amt);
#endif
		max_flow += amt;
	}
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    // input
    cin>>N>>M;
    sink = N+M+1;
    V = N+M+2;

    
    int temp;
    // A to sink
    for(int a = 1 ; a <= N; a++){
        cin>>temp;
        addEdge(a+M, sink, temp);
    }

    //and source to B
    vector<int> B(M);
	for(int b = 1 ; b <= M; b++){
        cin>>temp;
		B[b-1] = temp;
        //source to B
        addEdge(source, b, temp);
	}
	
    for(int b = 1; b <= M; b++){
        for(int a = 1+M; a < 1+M+N; a++){
            cin>>temp;
            addEdge(b,a, min(B[b-1],temp));
        }    
    }

#ifdef DEBUG_INPUT
for(int i = 0 ; i < V; i++){
	printf("edges[%d] : ",i);
	for(auto ep : edges[i]){
		printf("(%d,%d) ", ep->t, ep->c);
	}
	cout<<endl;
}

#endif
	
    // dinic();
    mcmf();

    cout<<max_flow<<endl;
    
    return 0;
}