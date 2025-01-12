#include <iostream>
#include <cstring>
#include <vector>

#define MAX_N 100
#define MAX_VIDX 10000
#define endl '\n'
using namespace std;
int N,M;
vector< vector<int> > board;

int coor2V[MAX_N][MAX_N] = {{-1}};
int coor2H[MAX_N][MAX_N] = {{-1}};
int vidx = 0; int hidx = 0;
vector<int> adj[MAX_VIDX]; // adj[a] : a번째 left노드의 인접 right 노드들
vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

bool isOccupiedV(int x, int y){
    return coor2V[x][y] > -1;
}

bool isOccupiedH(int x, int y){
    return coor2H[x][y] > -1;
}

bool placable(int x, int y){
    if( 0 <= x && x < N && 0 <= y && y < M) return board[x][y] < 2;
    return false;
}


bool dfs(int a){
    if( visited[a] ) return false;
    visited[a] = true;
    for(const auto & b : adj[a]){
        if( bMatch[b] == -1 || dfs( bMatch[b])){
            aMatch[a] = b;
            bMatch[b] = a;
            return true;
        }
    }
    return false;
}

int bipartiteMatch(int n, int m){
    aMatch = vector<int> (n, -1);
    bMatch = vector<int> (m, -1);
    int ret = 0;
    for(int i = 0; i < n; i++){
        visited = vector<bool> (n , false);
        if(dfs(i)) ret++;
    }
    return ret;
}

void solve(){
    cin>>N>>M;
    board = vector<vector<int>>(N, vector<int>(M,-1));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin>>board[i][j];
		}
        //reset
        fill(coor2V[i], coor2V[i] + M, -1);
        fill(coor2H[i], coor2H[i] + M, -1);
	}
	
    //create bipartite-graph
    vidx = 0; hidx = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if( placable(i,j) && board[i][j] != 1){
                if( !isOccupiedV(i,j)){ // create vertical Node
					int x1 = i;
					int y1 = j;
					while( placable(x1+1, y1)){
						x1++;
						coor2V[x1][y1] = vidx;
					}
                    coor2V[i][j] = vidx++;
                }
                
                if( !isOccupiedH(i,j)){//create horizontal Node
                    int x1 = i; 
					int y1 = j;
                    while( placable(x1, y1+1) ){
                        y1++;
                        coor2H[x1][y1] = hidx;
                    }
                    coor2H[i][j] = hidx++;
                }
                
				//add edges
                adj[coor2V[i][j]].push_back( coor2H[i][j] );
				// printf("adj[%d].push_back(%d) \n", coor2L[i][j], coor2R[i][j]);
            }
        }
    }
    
	// cout<<"vidx , hidx : "<<vidx<<","<<hidx<<endl;
    //bipartiteMatch
    cout<<bipartiteMatch(vidx, hidx)<<endl;
	for(int i = 0; i < vidx; i++) adj[i].clear();
}

int main(){
    solve();
    return 0;
}
