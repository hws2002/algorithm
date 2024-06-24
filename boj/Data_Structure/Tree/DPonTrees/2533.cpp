  #include <iostream>
#include <vector>

#define MAX_N 1'000'000

using namespace std;
vector<int> adj[MAX_N];

int N;
int cache[MAX_N][2] = {0};

/*
idx를 루트로 하는 서브 트리에서
필요한 최소 얼리 어답터의 수
*/

int dp(int idx, int isearly, int parent){
    int& ret = cache[idx][isearly];
    if(ret > 0) return ret;
    
    if(isearly){
        // is early adapter
        for(int i = 0; i < adj[idx].size(); i++){
            int neighbor = adj[idx][i];
            if( neighbor == parent) continue;
            ret += min( 1 + dp(neighbor, 1, idx) , dp(neighbor, 0, idx) );
        }
    } else {
        for(int i = 0 ; i < adj[idx].size(); i++){
            int neighbor = adj[idx][i];
            if( neighbor == parent) continue;
            ret += 1 + dp(neighbor, 1, idx);
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int u, v;
    for(int i = 0 ; i < N-1; i++){
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    
    // dp on tree
    cout<<min(dp(0,0, -1), 1 + dp(0,1, -1))<<endl;
    return 0;
}