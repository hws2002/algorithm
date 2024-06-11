// 13:22 - 13:44

// dfs + dp
#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
#define MAX_N 1'000
using namespace std;

int N,K,W,X,Y;
vector<int> D(MAX_N);
vector<int> adj[MAX_N];
int cache[MAX_N];

// here을 건설완료하는데 드는 최소시간을 출력한다
int dfs(int here){
    int& ret = cache[here];
    if(ret > -1) return ret;
    int time = 0;
    for(int i = 0 ; i < adj[here].size(); i++){
        int there = adj[here][i];
        time = max( time,  dfs(there) );
    }
    return ret = D[here] + time;
}

void solve(){
    cin>>N>>K;
    
    for(int i = 0 ; i < N; i++){
        cin>>D[i];
    }
    
    
    for(int i = 0 ; i < K; i++){
        cin>>X>>Y;
        adj[Y-1].push_back(X-1); // 역방향으로 담는다
    }
    
    cin>>W;
    
    //dfs
    cout<<dfs(W-1)<<endl;
    for(int i = 0 ; i < N; i++){
        adj[i].clear();
        cache[i] = -1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    std::fill(cache, cache + MAX_N, -1);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
