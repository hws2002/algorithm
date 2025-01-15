#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 2000
#define INF 1000000
#define all(v) v.begin(), v.end()

#define endl '\n'
using namespace std;


vector< pair<int,int> > adj[MAX_N];
vector< pair<int, pair<int, int> > > edges;

vector<int> weights;

const int src = 0;
int tgt;
int N,M;

struct DisjointSet{

public:
    vector<int> parent;
    vector<int> rank;
    DisjointSet(int n){
        parent.resize(n); rank.resize(n,0);
        for(int i = 0 ; i < n ;i++){
            parent[i] = i;
        }
    }
    
    int find(int u){
        if( u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v) return false;
        if( rank[u] < rank[v]) swap(u,v);
        parent[v] = u;
        if( rank[u] == rank[v]) rank[u]++;
        return true;
    }
};

void sortEdges(){
    for(int i = 0; i < N; i++){
        for(const auto & p : adj[i]){
            edges.push_back({p.second,{i, p.first}});
        }
    }
    sort( all(edges) );
}

int minUpperboundKruskal(int lidx){
    DisjointSet djs(N);
    
    int ub = -1;
    for(const auto & e : edges){
        int c = e.first; int u = e.second.first; int v = e.second.second;
        if( c < weights[lidx]) continue;
        ub = max(ub, c);
        djs.merge(u, v);
        if( djs.find(src) == djs.find(tgt) ) return ub;
    }
    return INF;
}

int minWeightDifference(){
    sortEdges();
    
    int ret = INF;
    //binary search
    
    //kruskal
    for(int i = 0; i < weights.size(); i++){
        ret = min (ret, minUpperboundKruskal(i) - weights[i]);
    }
    return ret;
}

void solve(){

    cin>>N>>M;
    int a,b,c;
    tgt = N-1;
    weights.resize(M); edges.clear();
    for(int i = 0; i <N; i++) adj[i].clear();

    for(int i = 0 ; i< M; i++){
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        weights[i] = c;
    }
    sort( all(weights));
    weights.erase( unique(all(weights)), weights.end() );
    
    cout<<minWeightDifference()<<endl;
}

int main(){
    int c; cin>>c; while(c--) solve();
    return 0;
}