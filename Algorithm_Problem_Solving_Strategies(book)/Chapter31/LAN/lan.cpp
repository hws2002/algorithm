#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#define all(v) v.begin(), v.end()
#define MAX_V 500

#define endl '\n'
using namespace std;

vector<int> xcoor;
vector<int> ycoor;
vector<pair<int,double> > adj[MAX_V];
int N,M;
    
struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
	vector<int> gsize;
    DisjointSet(int n = 0){
        parent.resize(n); rank.resize(n,0);
        gsize.resize(n,1);
        for(int i = 0 ; i < n ;i++){
            parent[i] = i;
        }
    }
    
    int find(int u){
        if( u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    
    bool merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v) return false;
        if( rank[u] < rank[v]) swap(u,v);
        parent[v] = u;
        if( rank[u] == rank[v]) rank[u]++;
		gsize[u] += gsize[v];
        return true;
    }
};

DisjointSet djs;

double kruskal(int V){
    double ret = 0;
    vector< pair<double, pair<int,int> > > edges;
    for(int i = 0 ; i < V; i++){
        for(const auto & p : adj[i]){
            edges.push_back({p.second, {i, p.first}});
        }  
    }
    
    sort(all(edges));
    
    int num_edge = 0;
    for(const auto & e : edges){
        int u = e.second.first; int v = e.second.second;
        if( djs.merge(u,v)){
            num_edge++;
            ret += sqrt(e.first);
        }
        if( num_edge >= V-1) break;
    }
    return ret;
}

double distance(int i, int j){
    return ( xcoor[i] - xcoor[j] ) * ( xcoor[i] - xcoor[j] ) + 
            ( ycoor[i] - ycoor[j] ) * ( ycoor[i] - ycoor[j] );
}

void createGraph(){
    for(int i = 0; i < N; i++){
        adj[i].clear();
        for(int j = 0; j < N; j++){
            if( djs.find(i) == djs.find(j)) continue;
            adj[i].push_back( {j, distance(i,j)} );
        }
    }
}

void solve(){

    cin>>N>>M;
    djs = DisjointSet (N);
    xcoor.resize(N); ycoor.resize(N);
    
    for(int i = 0; i < N; i++) cin>>xcoor[i];
    
    for(int i = 0; i < N; i++) cin>>ycoor[i];
    
    for(int i = 0; i < M; i++){
        int u,v;
        cin>>u>>v;
        djs.merge(u,v);
    }
	
    createGraph();
    printf("%.10f\n", kruskal(N));
}


int main(){
    int C;
    cin>>C;
    while(C--) solve();
}