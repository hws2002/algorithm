#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 1'000
#define MAX_M 100'000

using namespace std;


struct Edge{
public:
    int u,v,c;
    Edge(int u, int v, int c) : u(u), v(v), c(c){};
};

vector<Edge> Edges;


int N,M;

struct DisjointSet{
public:
    vector<int> p;
    vector<int> r;
    DisjointSet(int n){
        p.resize(n);
        for(int i = 0; i < n; i++)
            p[i] = i;
        r.resize(n,0);
    }
    
    int find(int u){
        if( p[u] == u) return u;
        return find(p[u]);
    }
    
    bool merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v) return false;
        
        if( r[u] > r[v]) swap(u,v);
        p[u] = v;
        if(r[u] == r[v]) r[v]++;
        return true;
    }
};

int mst(){
    DisjointSet set(N);
    int ret = 0;
	int num_e = 0;
    for(const auto &e : Edges){
        int u = e.u; int v = e.v; int c = e.c;
		// printf("u, v, c : %d, %d ,%d \n", u, v, c);
		if( set.merge(u,v)){
			ret += c;
			num_e++;
		}
		if(num_e >= N-1) return ret;
    }
	return ret;
}

int main(){
    cin>>N>>M;
    int a,b,c;

    for(int i = 0; i < M; i++){
        cin>>a>>b>>c;
        a--;b--;
        if( a != b)
            Edges.push_back(Edge(a,b,c));
    }

    sort(Edges.begin(), Edges.end(), [](const Edge & e1, const Edge & e2){
        return e1.c < e2.c;
    });

    cout<<mst()<<endl;
    return 0;
}