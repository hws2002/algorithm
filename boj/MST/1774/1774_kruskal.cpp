//mst - kruskal
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 1'000
#define MAX_M 1'000
using namespace std;
typedef long double ld;
double X[MAX_N];
double Y[MAX_N];

vector< pair<double, pair<int,int> > > Edges;
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

double kruskal(int Gsize, DisjointSet & set){

	double res = 0;
    int cnt = 0;
    double w;
    int u,v;

    for(auto e : Edges){
        w = e.first; u = e.second.first; v = e.second.second;
        if(set.find(u) == set.find(v)) continue;
        set.merge(u,v);
        res += w;
        cnt++;
        if(cnt >= Gsize-1) break;
    }

    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
	DisjointSet set(N);
    
    for(int i = 0 ; i < N; i++){
        cin>>X[i]>>Y[i];
    }
    

    //merge last m pair of nodes
    int u, v;
	int alreadymerged = 0;
    for(int i = 0; i < M; i++){
        cin>>u>>v;
        if(set.merge(u-1,v-1)) alreadymerged++;
    }
	
    cout<<"alreadymerged : "<<alreadymerged<<endl;
	
    //init first n edges
    for(int i = 0 ; i < N; i++){
        for(int j = i + 1; j < N; j++){
            Edges.push_back({hypot(X[i] - X[j], Y[i] - Y[j]),{i,j}});
        }
    }
    
	std::sort(Edges.begin(), Edges.end());
	
    //kruskal
    cout<<fixed;
    cout.precision(2);
    cout<<kruskal(N - alreadymerged,set)<<endl;
    // printf("%.2lf \n", kruskal(N, set));
    return 0;
}
