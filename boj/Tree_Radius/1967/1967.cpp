//음수 간선 x, 
// dijkstra

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
#include <queue>

#define INF (INT_MAX>>1)
using namespace std;

vector< pair<int,int> > adj[10'000];

int n; // 1<= n <= 10'000

int dijkstra(const int start, vector<int> & dists){
    fill(dists.begin() , dists.end(), INF);
    dists[start] = 0;
    priority_queue<pair<int,int> > pq;
    pq.push({-0,start});
    int farthest_v = 0;
    while(!pq.empty()){
        int here = pq.top().second;
        int dist = -pq.top().first;
        pq.pop();
        if(dists[here] < dist) continue;
        if(dists[farthest_v] < dist){
            farthest_v = here; 
        }
        for(int i = 0 ; i < adj[here].size(); i++){
            int next = adj[here][i].first;
            int cost = adj[here][i].second;
            if( dists[next] > dist + cost) {
                dists[next] = dist + cost;
                pq.push({-dists[next],next});
            }
        }
    }
    return farthest_v;
}

int main(){
    cin>>n;
    int p,c,w;
    for(int i = 0; i < n-1; i++){
        cin>>p>>c>>w;
        adj[p-1].push_back({c-1,w});
        adj[c-1].push_back({p-1,w});
    }

    //dijkstra
    int start = 0;
    vector<int> dists(n);
    //get farthest vertex idx
    start = dijkstra(start,dists);
    // cout<<"start : "<<start<<endl;
    // get farthest vertex idx again and use the vertex to get diameter
    cout<<dists[dijkstra(start,dists)]<<endl;   
    return 0;
}
