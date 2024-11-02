//MCMF

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
    int f,c,t,p;
    edge * inv;
    edge() : f(0), c(0), t(-1), p(0){};
    edge(int t_, int c_, int p_):
        f(0), c(c_), t(t_), p(p_), inv(nullptr){};
    int residual(){
        return c - f;
    }
};

vector<edge * > edges[MAX_N*2+2];

void addEdge(int u, int v, int c ,int p){
    edge * uv = new edge(v, c, p);
    edge * vu = new edge(u, 0, -p);
    uv->inv = vu;
    vu->inv = uv;
    edges[u].push_back(uv);
    edges[v].push_back(vu);
}

int min_cost = 0;
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
		vector<bool> inqueue(V,false);
		vector<pair<edge*,int>> parent(V,{nullptr,-1});
		vector<int> dist(V,numeric_limits<int>::max());
		int here = source;
		q.push(here);
		inqueue[here] = true;
		parent[here] = {nullptr,here};
		dist[here] = 0;
		while(!q.empty()){
			here = q.front(); q.pop();
			// printf("here : %d \n",here);
			inqueue[here] = false;
			for(auto ep : edges[here]){
				int next = ep->t;
				if( ep->residual() > 0){
					if( dist[next] > dist[here] + ep->p){
						dist[next] = dist[here] + ep->p;
						parent[next] = {ep,here};
						if(!inqueue[next]){
							q.push(next);
							inqueue[next] = true;
						}
					}
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
			single_cost += parent[here].first->p;
			parent[here].first->f += amt;
			parent[here].first->inv->f -= amt;
			here = parent[here].second;
		}
#ifdef DEBUG_EK
		printf("amt, total_cost :%d, %d \n",amt, single_cost*amt);
#endif
		max_flow += amt;
		min_cost += single_cost*amt;
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
        addEdge(a+M, sink, temp, 0);
    }

    //and source to B
    vector<int> B(M);
	for(int b = 1 ; b <= M; b++){
        cin>>temp;
		B[b-1] = temp;
        //source to B
        addEdge(source, b, temp, 0);
	}
	
	int C[MAX_N][MAX_N] = {0};
	for(int i = 0 ; i < M; i++){
		for(int j = 0 ; j < N; j++){
			cin>>C[i][j];
		}
	}
	
    for(int b = 1; b <= M; b++){
        for(int a = 1+M; a < 1+M+N; a++){
            cin>>temp;
            addEdge(b, a, C[b-1][a-M-1], temp);
        }
    }

#ifdef DEBUG_INPUT
for(int i = 0 ; i < V; i++){
	printf("edges[%d] : ",i);
	for(auto ep : edges[i]){
		printf("(%d,%d,%d) ", ep->t, ep->c, ep->p);
	}
	cout<<endl;
}

#endif
	
    // dinic();
    mcmf();

	cout<<max_flow<<endl;
    cout<<min_cost<<endl;
    
    return 0;
}