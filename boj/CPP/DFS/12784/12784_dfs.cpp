//TREE
#include <iostream>
#include <vector>

#define MAX_N 1'000
#define INF 1'000'000'000
#define endl '\n'
using namespace std;

int N,M; // M = N-1
vector<pair<int,int>> children[MAX_N];

int dfs(int h, int p, int prev_d){
    int ret = 0;
    for(auto & next : children[h]){
        int nxt = next.first; int d = next.second;
        if(nxt == p) continue;
        if(  children[nxt].size() == 1){
            ret += d;
        } else {
            ret += min( d, dfs(nxt, h, d));
        }
        if(ret >= prev_d) return prev_d;
    }
    return ret;
}

void solve(){
    cin>>N>>M;
    
    int u,v,d;
    for(int i = 0 ; i < N-1; i++){
        cin>>u>>v>>d;
        u--;v--;
        children[u].push_back({v,d});
        children[v].push_back({u,d});
    }
    
    cout<<dfs(0,-1, INF)<<endl;
    for(int i = 0; i < N; i++){
        children[i].clear();
    }
}

int main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}