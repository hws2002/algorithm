// disjoint set
// 22:40 ~ 22:55


#include <iostream>
#include <vector>

#define MAX_N 500'000
#define MAX_M 1'000'000

using namespace std;

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    DisjointSet(int n){
        parent = vector<int> (n);
        rank = vector<int> (n,1);
        for(int i = 0 ; i < n; i++){
            parent[i] = i;
        }
    }
    
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    void merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v ) return;
        if( rank[v] < rank[u]) swap(u,v);
        parent[u] = v;
        if( rank[u] == rank[v]) rank[v]++;
    }
};

int N,M;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    int u, v;
    DisjointSet set(N);
    for(int i = 1 ; i <= M; i++){
        cin>>u>>v;
        if( set.find(u) == set.find(v)){
            cout<<i<<endl;
            return 0;
        }
        set.merge(u,v);
    }
    cout<<0<<endl;
    return 0;    
}