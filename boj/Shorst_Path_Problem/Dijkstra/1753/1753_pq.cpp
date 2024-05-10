//방향그래프, dijkstra
// priority queue
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <limits.h>
#define endl '\n'
using namespace std;


int V,E; 
// 1<= V <= 20,000 
// 1<= E <= 300,000
int K;

vector<int> dijkstra(const int start, const vector<vector <pair <int,int> > > & Weights){
    vector<int> Dist(V+1, INT_MAX);
    Dist[start] = 0;
    priority_queue< pair<int, int> > PQ;
    PQ.push({0,start});
    int dist, u;
    while(!PQ.empty()){
        dist = -PQ.top().first;
        u = PQ.top().second;
        PQ.pop();
        if( Dist[u] < dist) continue; // 애초에 둘이 같은 상황이 발생 할 수 없음(밑에서 =를 안넣었기 때문에)
        for(auto weight : Weights[u]){
            if( Dist[weight.second] > dist + weight.first){ // 여기선 =를 넣으면 시간 복잡도가 늘어나겠지
                Dist[weight.second] = dist + weight.first;
                PQ.push({-Dist[weight.second],weight.second});
            }
            
        }
    }
    return Dist;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    cin>>V>>E;
    cin>>K;
    int u,v,w;
    vector< vector< pair<int,int> > > Weights(V+1);
    for(int i = 0 ; i < E; i++){
        cin>>u>>v>>w;
        Weights[u].push_back({w,v});
    }
    
    //solve
    vector<int> Dists = dijkstra(K, Weights);
    for(int i = 1 ; i < Dists.size(); i++){
        if(Dists[i] == INT_MAX) cout<<"INF"<<endl;
        else cout<<Dists[i]<<endl;
    }
    return 0;
}