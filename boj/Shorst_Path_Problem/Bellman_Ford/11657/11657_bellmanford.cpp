// 음수 간선 o, 음수 사이클 찾기 ->벨맨 포드

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>

#define MAX 500
#define INF INT_MAX
typedef long long ll;

using namespace std;

int N,M; // 1 <= N <= 500, 1 <= M <= 6000
vector<pair<int,int>> adj[MAX];

vector<ll> bellmanFord(int start){
    vector<ll> upper(N,INF);
    upper[start] = 0;
    bool updated;
    
    //iterate N times
    for(int iter = 0; iter < N; iter++){
        updated = false;
        for(int here = 0; here < N; here++){
            if(upper[here] >= INF) continue;
            for(int i = 0; i < adj[here].size(); i++){
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                if(upper[there] > upper[here] + cost){
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }
    
    if(updated) upper.clear();
    return upper;
}

int main(){
    //input
    cin>>N>>M;
    
    int A,B,C; // -10'000 <= C <= 10'000
    for(int i = 0 ; i < M; i++){
        cin>>A>>B>>C;
        adj[A-1].push_back({B-1,C});
    }
    //bellman-ford
    int start = 0;
    vector<ll> dists = bellmanFord(start);
    if(dists.empty()) {
        cout<<-1<<endl;
    } else {
        for(int i = 1; i < N; i++){
            if(dists[i] >= INF) cout<<-1<<endl;
            else cout<<dists[i]<<endl;
        }
    }
    return 0;
}
