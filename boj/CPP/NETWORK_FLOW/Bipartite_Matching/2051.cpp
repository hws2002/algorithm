#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 1'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'
using namespace std;

vector<int> adjAB[MAX_N];
vector<int> aMatch(MAX_N,-1);
vector<int> bMatch(MAX_N,-1);

vector<bool> visited;

int N,M;
int mVertexCoverSize = 0;

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(auto next : adjAB[here]){
        if( bMatch[next] == -1 || dfs(bMatch[next])){
            aMatch[here] = next;
            bMatch[next] = here;
            return true;
        }
    }
    return false;
}    

void bipartiteMatch(){
    FOR(i,0,N){
        visited = vector<bool> (N,false);
        if(dfs(i)) mVertexCoverSize++;
    }
}

vector<int> L; // unnecessary
vector<int> R;

vector<bool> coverB;

void bfs(const int start){
    queue<int> q;
    int here = start;
    q.push(here);
    visited[here] = true;
    while(!q.empty()){
        here = q.front(); q.pop();
        for(auto next : adjAB[here]){
            if( next == aMatch[here] || bMatch[next] == -1 || visited[bMatch[next]]) continue;
            q.push(bMatch[next]);
            visited[bMatch[next]] = true;
            coverB[next] = true;
        }
    }
}

void seperate(){
    coverB = vector<bool> (M,false);
    visited = vector<bool> (N,false);
    FOR(i,0,N){
        if( aMatch[i] == -1 && !visited[i]){
            bfs(i);
        }
    }
    
    FOR(i,0,N){
        if( aMatch[i] != -1 && !visited[i]){
            L.push_back(i);
        }
    }
    
    FOR(i,0,M){
        if( bMatch[i] != -1 && coverB[i]){
            R.push_back(i);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    int num_neighbor, neighbor;
    FOR(i,0,N){
        cin>>num_neighbor;
        FOR(j,0,num_neighbor){
            cin>>neighbor;
            adjAB[i].push_back(--neighbor);
        }
    }
    
    // bipartite matching
    bipartiteMatch();
    
    // output - maximum flow
    cout<<mVertexCoverSize<<endl;

    seperate();
    
    cout<<L.size()<<" ";
    for(auto e : L){
        cout<<e+1<<" ";
    } cout<<endl;
    
    cout<<R.size()<<" ";
    for(auto e : R){
        cout<<e+1<<" ";
    } cout<<endl;

    return 0;    
}