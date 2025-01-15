#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 1'000
#define MAX_M 100'000
#define INF 2'000'000'000

using namespace std;

struct Edge{
public:
    int u,v,c;
    Edge(int u, int v, int c) : u(u), v(v), c(c){};
};

// vector<Edge> Edges;

vector<pair<int,int>> Edges[MAX_N];
vector<int> dist;

int N,M;

int prim(){
    int ret = 0;
    priority_queue<pair<int, int>> pq; // <distance, nodenum>
    int h = 0; int d = 0;
    pq.push({-d,h});
    int num_n = 0;
    while(!pq.empty()){
        auto t = pq.top(); pq.pop();
        d = -(t.first); h = t.second;
		// printf("d, h : %d , %d \n", d,h);
        if( dist[h] > d) { // Q1 : dist[h] == INF로 바꿔도 될까? A : YES!
						   // Q2 : dist[h] >= d 로 바꿔도 될까? A : NO!
			// dist[h]가 INF가 아니라는건 이미 tree안에 포함되어 있다는 소리, 더 이상 건들지 말자
            dist[h] = d;
            ret += d; 
            if(++num_n >= N) return ret;
            // printf("num_n : %d \n", num_n);
            for(const auto & e : Edges[h]){
                int nxt = e.first; int c = e.second;
                if( dist[nxt] == INF) {// not yet discovered
                    pq.push({-c,nxt});
					// printf("pushing {%d, %d}\n", c, nxt);
				}
            }
        }
    }
    
    return ret;
}


//parent에 mst를 저장한다
int prim_pq(int src, vector<int> & parent){
    int ret = 0;
    priority_queue< pair<int, pair<int,int> > > pq; // {스패닝트리에서 u까지의 거리, {u, prarent of u}}
    vector<bool> intree(N,false);
    parent = vector<int> (N,-1);
    
    pq.push({-0,{src,src}});
    int num_add = 0;
    while( num_add < N){
        auto cup = pq.top(); pq.pop();
        int u = cup.second.first;
        if( intree[u]) continue;
        intree[u] = true;
        parent[u] = cup.second.second;
		ret += -cup.first;
        num_add++;
        for(const auto & e: Edges[u]){
            int nxt = e.first;
            if( !intree[nxt] ){
                pq.push({-e.second, {nxt, u}});
            }
        }
    }
    
    return ret;
}



int main(){
    cin>>N>>M;
    dist.resize(N,INF);

    int a,b,c;
    for(int i = 0; i < M; i++){
        cin>>a>>b>>c;
        a--;b--;
        if( a != b){
            // Edges.push_back(Edge(a,b,c));
        	Edges[a].push_back({b,c});
        	Edges[b].push_back({a,c});
		}
    }
	
	vector<int> p;
    cout<<prim_pq(0, p)<<endl;
	
    return 0;
}