#include <iostream>
#include <vector>

#define FOR(i,s,e) for(int i = s; i < e; i++)
#define MAX_N 80 // = MAX_M
#define endl '\n'
// #define DEBUG_EDGE

using namespace std;

int N,M;
bool MAP[MAX_N][MAX_N] = {false};
// bool adj[MAX_N*MAX_N>>1][MAX_N*MAX_N>>1] = {false};
vector<int> adj[MAX_N*(MAX_N+1)>>1];
vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

void addEdge(int r, int c){
    int aindex = N*(c/2) + r;
    int bindex = N*((c-1)/2) + r;
    for(int i = -1; i <=1; i++){
        if(0<= r+i && r+i < N && c+1 < M && MAP[r+i][c+1]) adj[aindex].push_back(aindex+i);
        if(0<= r+i && r+i < N && c-1 >=0 && MAP[r+i][c-1]) adj[aindex].push_back(bindex+i);
    }
    
}

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    // for(int next = 0; next < N*M/2; next++){
    for(auto next  : adj[here]){
        // if(adj[here][next]){
            if( bMatch[next] == -1 || dfs(bMatch[next])){
                aMatch[here] = next;
                bMatch[next] = here;
                return true;
            }
        // }
    }
    return false;
}

int res = 0;
void bipartiteMatching(){

    //reset
    aMatch = vector<int> (N*(M+1)/2, -1);
    bMatch = vector<int> (N*M/2, -1);

    FOR(i,0,N*(M+1)>>1){
        visited = vector<bool> (N*(M+1)/2, false);
        if(dfs(i)) res++;
    }
}

void solve(){
    //input
    cin>>N>>M;
    int available = N*M;
    char c;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < M; j++){
            cin>>c;
            if(c == '.') // 앉을 수 있는 자리
                MAP[i][j] = true;
            else {
                MAP[i][j] = false;
                available--;
            }
        }
    }
    
    //create edges
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j+=2){
            if(!MAP[i][j]) continue;
            addEdge(i,j);
        }
    }
    
#ifdef DEBUG_EDGE
FOR(i,0,N*(M+1)>>1){
    for(auto e : adj[i]){
        cout<<e<<" ";
    }
    cout<<endl;
}
#endif
    // bipartite matching
    res = 0;
    bipartiteMatching();
    cout<<available - res<<endl;
//reset
    for(int i = 0; i < N*(M+1)/2; i++){
        // fill(adj[i], adj[i] + N*M/2, false);
        adj[i].clear();
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin>>C;
    while(C--){
        solve();
    }
    return 0;
}