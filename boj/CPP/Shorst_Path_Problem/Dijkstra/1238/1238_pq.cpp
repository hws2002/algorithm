// 단방향, 음수간선x
// priority queue
// dijkstra

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits.h>

using namespace std;

int N;
vector< vector <pair < int, int > > > WeightsGo;
vector< vector <pair < int, int > > > WeightsCome;

vector<int> dijkstra(const int & start, vector< vector <pair < int, int > > >  & Weights){
    vector<int> Dists(N+1, INT_MAX);
    Dists[start] = 0;
    priority_queue< pair<int,int> > PQ;
    PQ.push({0,start});
    
    while(!PQ.empty()){
        int u = PQ.top().second;
        int dist = -PQ.top().first;
        PQ.pop();
        if( Dists[u] < dist) continue;
        for(auto next : Weights[u]){
            int v = next.first;
            int cost = next.second;
            if( Dists[v] > dist + cost){
                Dists[v] = dist + cost;
                PQ.push({-Dists[v],v});
            }
        }
    }
    
    return Dists;
}

int main(){
    //input
    int M,X;
    cin>>N>>M>>X;
    int u,v,w;
    WeightsGo = vector< vector < pair< int, int > > > (N+1);
    WeightsCome = vector< vector < pair< int, int > > > (N+1);
    while(M--){
        cin>>u>>v>>w;
        WeightsGo[u].push_back({v,w});
        WeightsCome[v].push_back({u,w});
    }
    
    //dijkstra
    vector<int> distsGo = dijkstra(X, WeightsGo);
    vector<int> distsCome = dijkstra(X, WeightsCome);
    
    //output
    int res = 0;
    for(int i = 1; i <= N; i++){
        res = max(res, distsGo[i] + distsCome[i]);
    }
    cout<<res<<endl;
    return 0;
}