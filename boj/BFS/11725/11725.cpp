#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector< vector<int> > Edges;
vector< int > Parents;

int main(){
    //input
    int N;
    cin>>N;
    Edges = vector<vector<int>>(N+1);
    Parents = vector<int>(N+1);
    int u,v;
    for(int i = 0 ; i < N-1; i++){
        cin>>u>>v;
        Edges[u].push_back(v);
        Edges[v].push_back(u);
    }
    
    
    //solve - bfs
    queue<int> q;
    // vector<bool> visit(N+1, false);
    q.push(1);
    // visit[1] = true;
    while(!q.empty()){
        int parent = q.front(); q.pop();
        for(auto child : Edges[parent]){
            if( !Parents[child] ){
                Parents[child] = parent;
                q.push(child);
            }
        }
    }
    
    //output
    for(int i = 2; i <= N; i++){
        cout<<Parents[i]<<endl;
    }
    
    return 0;
}