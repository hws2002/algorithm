#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 1000

#define endl '\n'
using namespace std;

int G,H;

vector<int> adj[MAX_N];
vector<bool> discovered;

enum
{
    UNWATCHED, 
    WATCHED, 
    SELECT
};
int ret;

int dfs(int here){
    discovered[here] = true;
    vector<int> children(3);
    for(const auto & c : adj[here]){
        if( !discovered[c] ) ++children[dfs(c)];
    }
    
    if( children[UNWATCHED]){
        ret++;
        return SELECT;
    }
    
    if( children[SELECT]) return WATCHED;
    return UNWATCHED;
}

void solve(){
    cin>>G>>H;
    int u,v;
    for(int i = 0; i < G; i++) adj[i].clear();

    
    for(int i = 0; i < H; i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ret = 0;
    discovered = vector<bool> (G, false);
    for(int i = 0; i < G; i++){
        if( !discovered[i] ){
            ret += dfs(i) == UNWATCHED;
        }
    }
    cout<<ret<<endl;
}



int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}