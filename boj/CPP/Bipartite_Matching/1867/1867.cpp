#include <iostream>
#include <vector>

#define MAX_N 500

using namespace std;

int n,k;
bool adj[MAX_N][MAX_N] = {false}; // adj[i][j] : i번째 행, j번째 열에 돌이 위치해 있는지
vector<int> aMatch (MAX_N, -1);
vector<int> bMatch (MAX_N, -1);
vector<bool> visited;
int res = 0;

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(int c = 0; c < n; c++){
        if(adj[here][c]){
            if( bMatch[c] == -1 || dfs( bMatch[c] )){
                aMatch[here] = c;
                bMatch[c] = here;
                return true;
            }
        }
    }
    return false;
}

int main(){
    cin>>n>>k;
    int c,r;
    for(int i = 0; i < k; i++){
        cin>>c>>r;
        c--;r--;
        adj[c][r] = true;
    }
    
    //maxflow - 첫번째 행부터 시작
    for(int i = 0; i < n; i++){
        visited = vector<bool> (n, false);
        if(dfs(i)) res++;
    }

    cout<<res<<endl;
    return 0;
}