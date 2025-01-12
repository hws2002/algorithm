#include <iostream>
#include <vector>

#define MAX_N 1'000
#define endl '\n'
using namespace std;

int N,M;

vector< pair<int, int> > adj;
vector<bool> visited;
vector<int> aMatch;
vector<int> bMatch;

bool dfs(int b){
    if( visited[b] ) return false;
    visited[b] = true;
    for(int a = adj[b].first;  a <= adj[b].second; a++){
        if( aMatch[a] == -1 || dfs( aMatch[a])){
            bMatch[b] = a;
            aMatch[a] = b;
            return true;
        }
    }
    return false;
}

int bipartiteMatch(int n, int m){
    aMatch = vector<int> (n, -1);
    bMatch = vector<int> (m, -1);
    int ret = 0;
    for(int i = 0; i < m; i++){
        visited = vector<bool> (m, false);
        if(dfs(i)) ret++;
    }
    return ret;
}

void solve(){
	cin>>N>>M;
	int a,b;
	//reset
	adj = vector< pair<int,int> > (M, {-1,-1});
	
	for(int i = 0;  i < M; i++){
		cin>>a>>b;
		a--;b--;
		adj[i] = {a,b};
	}
	cout<<bipartiteMatch(N,M)<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int T; cin>>T; while(T--) solve();
	return 0;
}