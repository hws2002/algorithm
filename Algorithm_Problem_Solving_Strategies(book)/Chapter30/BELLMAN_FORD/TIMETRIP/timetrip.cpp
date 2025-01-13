#include <iostream>
#include <vector>
#include <queue>

#define MAX_G 100
#define INF 1000000
using namespace std;

int G,W;
vector< pair<int,int> > oadj[MAX_G];
vector< pair<int,int> > radj[MAX_G];
vector<bool> inncycle;
const int src = 0;
const int tgt = 1;

vector<int> spfa(int src, vector<pair<int,int>> * adj){
    queue<int> q;
    vector<int> dist(G,INF);
    q.push(src); dist[src] = 0;
    int iter = 1; int qsize1 = 1; int qsize2 = 0;

    while( iter < G && qsize1 ){
        int h = q.front(); q.pop();
        for(const auto & e : adj[h]){
            int nxt = e.first; int cost = e.second;
            if( dist[nxt] > dist[h] + cost){
                dist[nxt] = dist[h] + cost;
                q.push(nxt);
                qsize2++;
            }
        }

        if( --qsize1 <= 0){
            iter++;
            qsize1 = qsize2;
            qsize2 = 0;
        }
    }
    

    inncycle = vector<bool> (G, false);
    while(!q.empty()){
        int h = q.front(); q.pop();
        for(const auto & e: adj[h]){
            int nxt = e.first; int cost = e.second;
            if( dist[nxt] > dist[h] + cost){
                dist[nxt] = dist[h] + cost;
                if( !inncycle[nxt]){
                    inncycle[nxt] = true;
                    q.push(nxt);
                }
            }
        }
    }
    return dist;
}

void solve(){
    cin>>G>>W;
    int a,b,d;
    
    for(int i = 0; i < G; i++){
        oadj[i].clear();
        radj[i].clear();
    }
    
    for(int i = 0; i < W; i++){
        cin>>a>>b>>d;
        oadj[a].push_back({b,d});
        radj[a].push_back({b,-d});
    }
    
    vector<int> shortestDist = spfa(src, oadj);
    if( shortestDist[tgt] == INF){
        cout<<"UNREACHABLE"<<endl;
    } else {
        if( inncycle[tgt] ) cout<<"INFINITY"<<" ";
        else cout<<shortestDist[tgt]<<" ";
        
        shortestDist = spfa(src,radj);
        if(inncycle[tgt]) cout<<"INFINITY"<<endl;
        else cout<<-shortestDist[tgt]<<endl;
    }

}

int main(){
    int C; cin>>C; while(C--) solve(); return 0;
}