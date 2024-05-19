//SPFA
#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
#include <queue>

#define MAX_V 500
#define INF LLONG_MAX
typedef long long ll;
using namespace std;


vector< pair<int,int>> adj[MAX_V];
int N,M;

void printVector(vector<ll> & v){
    for(auto item : v){
        cout<<item<<" "<<endl;
    }
}

void printVector(vector<pair<int,int>> & v){
    for(auto item : v){
        cout<<"("<<item.first<<","<<item.second<<")"<<endl;
    }
}

vector<ll> spfa(const int & start){
    vector<ll> dists (N,INF);
    dists[start] = 0;
    queue<int> q;
    q.push(start);
    vector<bool> inqueue(N,false);
    inqueue[start] = true;
    vector<int> cnt_updated(N,0);
    bool negative_cycle = false;
    while(!q.empty()){
        int here = q.front(); 
        q.pop();
        inqueue[here] = false;
        
        for(int i = 0; i < adj[here].size(); i++){
            int there = adj[here][i].first;
            int cost = adj[here][i].second;
            
            if( dists[there] > dists[here] + cost){
                dists[there] = dists[here] + cost;

                if(!inqueue[there]){
                    q.push(there);
                    inqueue[there] = true;
                    cnt_updated[there] += 1;
                    if(cnt_updated[there] > N) {
                        negative_cycle = true; 
                        break;
                    }
                }
            }
        }
        if(negative_cycle) break;
    }
    
    if(negative_cycle) dists.clear();
    return dists;
}


int main(){
    cin>>N>>M;
    int A,B,C;
    for(int i = 0 ; i < M; i++){
        cin>>A>>B>>C;
        adj[A-1].push_back({B-1,C});
    }
    //solve
    int start = 0;
    vector<ll> dists = spfa(start);
    if(dists.empty()) cout<<-1<<endl;
    else {
        for(int i = 1; i < N; i++){
            if(dists[i] >= INF) cout<<-1<<endl;
            else cout<<dists[i]<<endl;
        }
    }
    return 0;
}
