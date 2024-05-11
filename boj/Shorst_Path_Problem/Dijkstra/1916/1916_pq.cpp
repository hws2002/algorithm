// 음수간선x, 방향그래프
// priority queue
#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#define endl '\n'

using namespace std;

int N,M;
// 1<= N <= 1000
// 1<= M <= 100,000
vector<int> Dist(1001, INT_MAX);

void dijkstra(const int & start, const vector< vector< pair<int, int> > > & Weights){
    priority_queue< pair<int, int> > PQ;
    Dist[start] = 0;
    PQ.push({0,start});
    while(!PQ.empty()){
        int u = PQ.top().second;
        int dist = -PQ.top().first;
        PQ.pop();
        if( Dist[u] < dist ) continue;
        
        for( auto next : Weights[u]){
            int cost = next.first;
            int v = next.second;
            if( Dist[v] > cost + dist){
                Dist[v] = cost + dist;
                PQ.push({-1 * (cost + dist), v});
            }
        }
    }
    
    return ;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    cin>>M;
    int u,v,w;
    vector< vector< pair<int, int> > > Weights(N+1);
    for(int i = 0; i < M; i++){
        cin>>u>>v>>w; // 0 <= w < 100000
        Weights[u].push_back({w,v});
    }
    
    
    //solve
    int start, end;
    cin>>start>>end;
    dijkstra(start, Weights);
    
    //output
    cout<<Dist[end];
    return 0;
}