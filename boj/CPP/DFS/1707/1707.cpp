//dfs1
#include <iostream>
#include <vector>

#define MAX_V 20'000
#define MAX_E 200'000
#define endl '\n'

using namespace std;

int V,E;
vector<int> Edges[MAX_V];

bool dfs(vector<int> & isredteam, const int here, int lastteamnum){

    isredteam[here] = (lastteamnum == 1 ? 2 : 1);
    for(auto next : Edges[here]){
        if(!isredteam[next]){
            isredteam[next] = lastteamnum;
            if(!dfs(isredteam, next, isredteam[here])) return false;
        } else {
            if( isredteam[next] != lastteamnum) return false;
        }
    }
    return true;
}

void solve(){
    cin>>V>>E;
    
    vector<int> isredteam(V,0);
    
    int u,v;
    for(int i = 0; i < E; i++){
        cin>>u>>v;
        Edges[u-1].push_back(v-1);
        Edges[v-1].push_back(u-1);
    }
    
    //try all
    bool bipartite = true;
    for(int i = 0; i < V; i++){
        if(!isredteam[i]) 
            bipartite = dfs(isredteam,i,1);
        if(!bipartite) break;
    }
    
    if(bipartite) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    
    //clear edge
    for(int i = 0; i < V; i++){
        Edges[i].clear();
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int K;
    cin>>K;
    while(K--){
        solve();
    }
    return 0;
}
