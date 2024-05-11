// 음수간선x, 방향그래프, 경로출력
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
int PREV[1001] = {0};
void dijkstra(const int & start, const int & end, const vector< vector< pair<int, int> > > & Weights){
    priority_queue< pair<int, pair<int,int> > > PQ;
    Dist[start] = 0;
    PQ.push({0,make_pair(start, 0)});
    while(!PQ.empty()){
        int dist = -PQ.top().first;
        int u = PQ.top().second.first;
        int prev_u = PQ.top().second.second;
        PQ.pop();
        if( Dist[u] < dist ) continue;
        PREV[u] = prev_u;
        if( u == end) break;
        for( auto next : Weights[u]){
            int cost = next.first;
            int v = next.second;
            if( Dist[v] > cost + dist){
                Dist[v] = cost + dist;
                PQ.push({-1 * (cost + dist), make_pair(v,u)});
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
    int start,end;
    cin>>start>>end;
    dijkstra(start, end, Weights);
    
    //output
    cout<<Dist[end]<<endl;
    vector<int> path;
    u = end;
    while( u != 0) {
        path.push_back(u);
        u = PREV[u];
    }
    cout<<path.size()<<endl;
    for(int i = path.size()-1; i>=0 ; i--){
        cout<<path[i]<<" ";
    }
    cout<<endl;
    return 0;
}