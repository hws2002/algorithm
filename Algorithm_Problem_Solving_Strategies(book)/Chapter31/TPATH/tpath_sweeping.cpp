#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 2000
#define INF 1000000
#define all(v) v.begin(), v.end()

#define endl '\n'
using namespace std;


vector< pair<int,int> > adj[MAX_N];
vector< pair<int, pair<int, int> > > edges;

vector<int> weights;

const int src = 0;
int tgt;
int N,M;

bool hasPath(int lo, int hi){
    queue<int> q;
    vector<bool> visited(N, false);
    q.push(src); visited[src] = true;
    while(!q.empty() && visited[tgt] == false){
        int h = q.front(); q.pop();
        for(const auto & p : adj[h]){
            if( lo <= p.second  && p.second <= hi){
                int there = p.first;
                if(!visited[there]){
                    q.push(there);
                    visited[there] = true;
                }
            }
        }
    }
    return visited[tgt];
}

int minUpperboundBinary(int lidx){
    
    int lo = lidx; int hi = weights.size();
    int mid = (lo + hi) >> 1;
    while( lo < hi ){
        mid = ( lo + hi ) >> 1;
        if( hasPath( weights[lidx], weights[mid] ) ){
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    
    if( hi == weights.size()) return INF;
    return weights[hi];
}

int minWeightDifference(){
    
    int ret = INF;
    //binary search
    // for(int i = 0 ; i < weights.size(); i++){
    //     ret = min( ret, minUpperboundBinary(i) - weights[i]);
    // }
    
    // //kruskal
    // for(int i = 0; i < weights.size(); i++){
    //     ret = min (ret, minUpperboundKruskal(i) - weights[i]);
    // }
    
    //sweeping
    int lo = 0; int hi = 0;
    while(lo < weights.size() && hi < weights.size()){
        while( hi < weights.size() && !hasPath(weights[lo], weights[hi])){
            hi++;
        }
        
        while( lo <= hi && hasPath( weights[lo], weights[hi] )){
            ret = min(ret, weights[hi] - weights[lo]);
            lo++;
        }
    }
    
    return ret;
}

void solve(){

    cin>>N>>M;
    int a,b,c;
    tgt = N-1;
    weights.resize(M); edges.clear();
    for(int i = 0; i <N; i++) adj[i].clear();

    for(int i = 0 ; i< M; i++){
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        weights[i] = c;
    }
    sort( all(weights));
    weights.erase( unique(all(weights)), weights.end() );
    
    cout<<minWeightDifference()<<endl;
}

int main(){
    int c; cin>>c; while(c--) solve();
    return 0;
}