// 음수 간선 o, 음수 사이클 찾기
// bellman-ford

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
#include <queue>

#define MAX_V 500
#define INF INT_MAX

// #define DEBUG_SPFA
using namespace std;
#ifdef DEBUG_SPFA

void printQueue(queue<int> q){
    while(!q.empty()){
        cout<<q.front()+1<<" ";
        q.pop();
    }    
    cout<<endl;
}
void printVector(vector<int> & v){
    for(auto item : v){
        cout<<item<<" ";
    }
    cout<<endl;
}
#endif

int N,M,W;
vector<pair<int,int>> adjM[MAX_V];
vector<pair<int,int>> adjW[MAX_V];
vector<int> dists;

bool spfa(const int start){
    dists[start] = 0;
    queue<int> q;
    q.push(start);
    vector<bool> inqueue(N,false);
    inqueue[start] = true;
    vector<int> cnt_updated(N,0);
    cnt_updated[start]++;
    while(!q.empty()){
#ifdef DEBUG_SPFA
printQueue(q);
#endif
        int here = q.front();
        q.pop();
        inqueue[here] = false;
        
        //wormhole
        for(int i = 0 ; i < adjW[here].size(); i++){
            int there = adjW[here][i].first;
            int cost = adjW[here][i].second;
            
            if(dists[there] > dists[here] + cost){
                dists[there] = dists[here] + cost;
                if(!inqueue[there]){
                    q.push(there);
                    inqueue[there] = true;
                    cnt_updated[there]++;
                    if(cnt_updated[there] >= N) {
                        return true;
                    }
                }
            }
        }
        
        //road
        for(int i = 0 ; i < adjM[here].size(); i++){
            int there = adjM[here][i].first;
            int cost = adjM[here][i].second;
            if(dists[there] > dists[here] + cost){
                dists[there] = dists[here] + cost;
                if(!inqueue[there]){
                    q.push(there);
                    inqueue[there] = true;
                    cnt_updated[there]++;
                    if(cnt_updated[there] >= N) {
                        return true;
                    }
                }
            }
        }
#ifdef DEBUG_SPFA
printVector(cnt_updated);
printVector(dists);
#endif
    }
    
    return false;
}

void solve(){
    cin>>N>>M>>W;
    int S,E,T; // 1<= T <= 10'000
    
    //road
    for(int i = 0 ; i < M; i++){
        cin>>S>>E>>T;
        adjM[S-1].push_back({E-1,T});
        if(E != S) adjM[E-1].push_back({S-1,T});
    }
    //wormhole
    for(int i = 0 ; i < W; i++){
        cin>>S>>E>>T;
        adjW[S-1].push_back({E-1,-T});
        if(S == E && T < 0){
            cout<<"YES"<<endl; return;
        }
    }
    
    //spfa , output
    
    dists = vector<int> (N,INF);
    for(int start = 0; start < N; start++){
        if(dists[start] >= INF) {
            if(spfa(start)){
                cout<<"YES"<<endl;
                for(int i = 0; i < N; i++){
                    adjW[i].clear();
                    adjM[i].clear();
                    dists.clear();
                }
                return ;
            }
        }
    }
    for(int i = 0 ; i < N ; i++){
        adjW[i].clear();
        adjM[i].clear();
    }
    dists.clear();
    cout<<"NO"<<endl;
}

int main(){
    int TC;
    cin>>TC;
    while(TC--){
        solve();
    }
    return 0;
}
