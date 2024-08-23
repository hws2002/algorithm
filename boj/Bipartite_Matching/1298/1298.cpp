#include <iostream>
#include <vector>

#define MAX_N 100
#define FOR(i,s,e) for(int i = s; i < e; i++)
using namespace std;

int N,M;
vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

vector<int> adjAB[MAX_N];


int maxflow = 0;

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(auto next : adjAB[here]){
        if( bMatch[next] == -1 || dfs(bMatch[next])) {
            aMatch[here] = next;
            bMatch[next] = here;
            return true;
        }
    }
    return false;
}


void bipartiteMatch(){
    //reset
    aMatch = vector<int> (N,-1);
    bMatch = vector<int> (N,-1);
    FOR(i,0,N){
        visited = vector<bool> (N,false);
        if( dfs(i) ) maxflow++;
    }
}

int main(){
    cin>>N>>M;
    //create edges
    int u,v;
    FOR(i,0,M){
        cin>>u>>v;
        u--;v--;
        adjAB[u].push_back(v);
    }
    
    // 이분매칭
    bipartiteMatch();
    
    cout<<maxflow<<endl;
    return 0;
}