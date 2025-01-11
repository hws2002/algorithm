#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#define MAX_V 10000
#define INF 1000000000
#define endl '\n'
using namespace std;

const int src = 0;
int tgt;
int n,m;
vector<pair<int,double>> adj[MAX_V];

vector<double> dijkstra(int src){
    priority_queue< pair<double,int > > pq;
    vector<double> dist(n,INF);
    pq.push({-0,src});
    dist[src] = 0;
    while(!pq.empty()){
        const auto p = pq.top(); pq.pop();
        int h = p.second; double cost = -p.first;
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
    cin>>n>>m;
	tgt = n - 1;
    for(int i = 0; i < n; i++){
        adj[i].clear();
    }
    
    int a,b;
	double c;
    for(int i = 0; i < m; i++){
        cin>>a>>b>>c;
		double logc = log(c);
        adj[a].push_back({b,logc});
        adj[b].push_back({a,logc});
    }
    
    auto dist = dijkstra(src);
	printf("%.10f \n", exp(dist[tgt]));
}

int main(){
    int t;cin>>t; while(t--) solve();
    return 0;
}