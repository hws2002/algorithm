#include <iostream>
#include <queue>
#include <vector>

#define MAX_V 1000
#define INF 1000000000

using namespace std;

int V,E;
const int src = 0;

vector<pair<int,int>> adj[MAX_V+1];

vector<int> dijkstra(int src){
    priority_queue< pair<int,int > > pq;
    vector<int> dist(V,INF);
    pq.push({-0,src});
    dist[src] = 0;
    while(!pq.empty()){
        const auto p = pq.top(); pq.pop();
        int h = p.second; int cost = -p.first;
        if(cost > dist[h]) continue;
        for(const auto & np : adj[h]){
            if( dist[np.first] > cost + np.second) {
                dist[np.first] = cost + np.second;
                pq.push({-dist[np.first], np.first});
            }
        }
    }
    return dist;
}

void solve(){
    cin>>V>>E;
    int n,m;
    cin>>n>>m;
    for(int i = 0; i <= V; i++){
        adj[i].clear();
    }
    
    int a,b,t;
    for(int i = 0; i < E; i++){
        cin>>a>>b>>t;
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }
    
    vector<int> fireplace;
    for(int i = 0; i < n; i++){ // 화재장소
        cin>>a;
        fireplace.push_back(a);
    }
    
    for(int i = 0; i <m; i++){ // 소방서
        cin>>a;
        adj[src].push_back({a,0});
    }
    
    auto dist = dijkstra(src);
    int ret = 0;
    for(const auto & fp : fireplace){
        ret += dist[fp];
    }
    cout<<ret<<endl;
}

int main(){
    int c;cin>>c; while(c--) solve();
    return 0;
}