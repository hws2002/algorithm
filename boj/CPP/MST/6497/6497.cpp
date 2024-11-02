#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_M 200'000
#define MAX_N 200'000

using namespace std;

vector< pair<int, pair<int,int> > >Edges;
int N,M;
struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    
    DisjointSet(const int n){
        rank.resize(n,0);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    
    //find
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    //merge
    bool merge(int u, int v){
        u = find(u); v = find(v);    
        if( u == v ) return false;
        if(rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if( rank[u] == rank[v]) rank[v]++;
        return true;
    }
};

int kruskal(int gsize, DisjointSet & set){
    
    int res = 0;
    int cnt = 0;
    int u,v,w;
    for(auto e : Edges){
        w = e.first; u = e.second.first; v = e.second.second;
        if(set.find(u) == set.find(v)) continue;
        set.merge(u,v);
		res += w;
        cnt++;
        if(cnt >= gsize-1) break;
    }
    return res;
}

int main(){
    int x, y ,z;
	int total = 0;
	while(true){
		cin>>M>>N;
		if( M == 0 && N == 0 ) break;
		DisjointSet set(M);
		total = 0;
		for(int i = 0 ; i < N; i++){
			cin>>x>>y>>z;
			Edges.push_back({z,{x,y}});
			total += z;
		}
		sort(Edges.begin(), Edges.end());
    	cout<<total - kruskal(M,set)<<endl;	
		Edges.clear();
	}
    return 0;
}
