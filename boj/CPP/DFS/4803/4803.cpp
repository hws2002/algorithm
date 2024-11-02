//dfs

// 무방향 

#include <iostream>
#include <vector>

#define MAX_N 500

using namespace std;

int n,m;

vector<int> adj[MAX_N];
vector<int> discovered;
int cnt = 0;

// return true if the graph containing node 'here' is tree
bool dfs(int here, const int last){
    bool istree = true;
    discovered[here] = ++cnt;
    for(auto next : adj[here]){
        if(next == last) continue;
        if(!discovered[next]){ // 트리간선
            if(!dfs(next,here)) istree = false;
        } else if(discovered[next] < discovered[here]){ // 역방향간선
            //cycle exists
            istree = false;
        }
    }
    
    return istree;
}

void solve(const int & casenum){
    //reset
    discovered.clear();
    discovered.resize(n,0);
    int u,v;
    for(int i = 0; i < m; i++){
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    
    //dfsAll
    int num_tree = 0;
    for(int i = 0 ; i < n ; i++){
        cnt = 0;
        // printf("discovered[%d] : %d ", i, discovered[i]);
        if(!discovered[i]) {
            if(dfs(i,-1)){
                // printf("dfs(%d) is true \n", i);
                num_tree++;
            }
        }
    }
    
    printf("Case %d: ", casenum);
    if(num_tree <= 0){
        printf("No trees.\n");
    } else if (num_tree <=1){
        printf("There is one tree.\n");
    } else {
        printf("A forest of %d trees.\n", num_tree);
    }
    
    //reset
    for(int i = 0; i < n ;i++) {
        adj[i].clear();
    }
}

int main(){
    int casenum = 0;
    while(true){
        cin>>n>>m;
        if(n <= 0 && m <= 0 ) break;
        solve(++casenum);
    }
    return 0;
}