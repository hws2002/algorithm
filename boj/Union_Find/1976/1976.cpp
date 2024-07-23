#include <iostream>
#include <vector>

#define MAX_N 200
#define MAX_M 1'000
using namespace std;

int N,M;
// bool MAP[MAX_N][MAX_N] = {false};

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    
    DisjointSet(const int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i = 0; i < n; i++){
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

int main(){
    cin>>N>>M;
    
    DisjointSet set(N);
    
    bool temp;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            // cin>>MAP[i][j];
            cin>>temp;
            if( j <= i ) continue;
            if(temp)
                set.merge(i,j);
        }
    
    bool canTravel = true;
    int u,v;
    
    cin>>u;
    v = u;
    for(int i = 1; i < M; i++){
        u = v;
        cin>>v;
        if(set.find(u-1) != set.find(v-1)) { canTravel = false; break;}
    }
    
    if(canTravel) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
