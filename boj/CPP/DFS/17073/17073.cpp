#include <iostream>
#include <vector>

#define MAX_N 500'000
using namespace std;

vector<int> adj[MAX_N];

int N;
double W;
double num_leaf = 0;

void dfs(int h,int p){
    
    bool leaf = true;
    for(const auto & nxt : adj[h]){
        if(nxt == p) continue;
        dfs(nxt,h); leaf = false;
    }
    
    if(leaf) num_leaf++;
    
}  

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>W;
    
    int u,v;
    for(int i = 0; i < N-1; i++){
        cin>>u>>v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    
    //
    int src = 0;
    dfs(src,-1);
    
    printf("%.4f \n", W/num_leaf);
    return 0;
}