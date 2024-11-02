//bfs

#include <iostream>
#include <vector>
#include <queue>

#define MAX_V 20'000
#define MAX_E 200'000
#define endl '\n'

using namespace std;

int V,E;
vector<int> Edges[MAX_V];

bool bfs(vector<int> & isredteam, const int start){
    
    queue<int> q;
    q.push(start);
    int isred = isredteam[start] = 1;
    
    while(!q.empty()){
        int here = q.front();
        isred = isredteam[here];
        q.pop();
        for(auto next : Edges[here]){        
            if(!isredteam[next]){
                isredteam[next] = (isred == 1 ? 2 : 1);
                q.push(next);
            } else {
                if( isred == isredteam[next]) return false;
            }
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
            bipartite = bfs(isredteam,i);
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