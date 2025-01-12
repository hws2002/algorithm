#include <iostream>
#include <vector>

#define MAX_N 1'000
#define MAX_M 1'000
using namespace std;

int N,M;

bool adj[MAX_N][MAX_N] = {0}; // adj[i][j] : i번째 직원이 j번째 일을 할 수 있는지
vector<int> workerMatch(MAX_N,-1); // workerMatch[i] : i번째 직원과 연결되어 있는 일의 index 
vector<int> workMatch(MAX_N,-1); // workMatch[i] : i번째 일과 연결되어 있는 직원의 index
vector<bool> visited;

bool dfs(int worker){
    if(visited[worker]) return false;
    visited[worker] = true;

    for(int work = 0; work < M ; work++){
        if(adj[worker][work]){
            if( workMatch[work] == -1 || dfs(workMatch[work])){
                workerMatch[worker] = work;
                workMatch[work] = worker;
                return true;
            }
        }
    }
    return false;
}

int res = 0;

void bipartiteMatch(){
    //reset 
    for(int i = 0; i < N; i++){
        for(int j = 0;  j < 2; j++){
            visited = vector<bool> (N, false);    
            if(dfs(i)) res++;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    int work, num_work;
    for(int i = 0; i < N; i++){
        cin>>num_work;
        while(num_work--){
            cin>>work;
            adj[i][--work] = true;
        }
    }
    
    //bipartite match
    bipartiteMatch();
    
    cout<<res<<endl;
    return 0;
}