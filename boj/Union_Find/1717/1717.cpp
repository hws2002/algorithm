#include <iostream>
#include <vector>

#define MAX_N 1'000'001
#define MAX_M 100'000
#define endl '\n'
using namespace std;

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    
    DisjointSet(const int n){
        parent.resize(n+1);
        rank.resize(n+1,0);
        for(int i = 0; i <= n; i++){
            parent[i] = i;
        }
    }
    
    //find
    int find(const int u){
        if( parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    //merge
    bool merge(int u, int v){
        u = find(u);
        v = find(v);
        if( u == v) return false;
        if( rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if(rank[u] == rank[v]) rank[v]++;
        return true;
    }
};

int n,m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    DisjointSet set(n);
    
    int op = -1; int a,b;
    for(int i = 0; i < m; i++){
        cin>>op>>a>>b;
        if(op){
            // find
            if(set.find(a) == set.find(b)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        } else {
            set.merge(a,b);
        }
    }
    
    return 0;
}