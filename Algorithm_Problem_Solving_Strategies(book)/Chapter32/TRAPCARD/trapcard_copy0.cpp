#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_H 20
#define MAX_V 400

// #define DEBUG_INPUT
#define endl '\n'
using namespace std;
typedef pair<int,int> coor;

int H,W;
vector<int> adj[MAX_V];
vector< vector<int> > board;
vector< vector<int> > res;
int num_trap = 0;


vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

vector<bool> aVisited;
vector<bool> bVisited;
vector<bool> aChosen;
vector<bool> bChosen;

vector<coor> aidx2coor(MAX_V>>1);
vector<coor> bidx2coor(MAX_V>>1);

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

void takeover(int a){
    aChosen[a] = true;
    for(const auto & b : adj[a]){
        if( bChosen[b]){
            bChosen[b] = false;
            takeover( bMatch[b] ); // 재귀 호출
        }
    }
}

void calcMaxIndependentSet(int n, int m){
    vector<int> A_M;
    aChosen = vector<bool> (n, false);
    bChosen = vector<bool> (m, true); // B에 속한 모든 정점들은 고르고
    
    for(int i = 0 ; i < n; i++){
        if( aMatch[i] == -1){ // A는 A-M만 고른다
            aChosen[i] = true;
            A_M.push_back(i);
        }
    }
    
    for(const auto a : A_M){
        takeover(a);
    }
}    
  


void setRes(int n,int m){
    for(int i = 0; i < n; i++){
        if( aChosen[i]){
			int x = aidx2coor[i].first; int y = aidx2coor[i].second;
            num_trap++;
            res[x][y] = 2;
        }
    }
    for(int i = 0; i < m; i++){
        if( bChosen[i]) {
			int x = bidx2coor[i].first; int y = bidx2coor[i].second;
			num_trap++;
            res[x][y] = 2;
        }
    }
}

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void fillres(int x, int y){
    queue<coor> q;

    //modeling
    q.push({x,y});
    int aidx = 0; int bidx = 0;

    board[x][y] = 2;
    if ( (x+y) & 1 ) {
        aidx2coor[aidx] = {x,y};
        aidx++;
    } else {
        bidx2coor[bidx] = {x,y};
        bidx++;
    }
	
    while(!q.empty()){
        auto & c = q.front(); q.pop();
        x = c.first; y = c.second;
        if( (x+y) & 1){
            for(int i = 0;  i <4; i++){
                int nx = x + dx[i]; int ny = y + dy[i];
                if( 0 <= nx && nx < H && 0 <= ny && ny < W && board[nx][ny] != 0){
                    if( board[nx][ny] == 1){ // not discovered yet
                        board[nx][ny] = bidx+2;
                        bidx2coor[bidx] = {nx,ny};
                        bidx++;
                        q.push({nx,ny});
                    }

                    // add edge
                    adj[board[x][y] - 2].push_back(board[nx][ny]-2);
                }
            }
        } else {
            for(int i = 0;  i <4; i++){
                int nx = x + dx[i]; int ny = y + dy[i];
                if( 0 <= nx && nx < H && 0 <= ny && ny < W && board[nx][ny] != 0){
                    if( board[nx][ny] == 1){ // not discovered yet
                        board[nx][ny] = aidx+2;
                        aidx2coor[aidx] = {nx,ny};
                        aidx++;
                        q.push({nx,ny});
                    }
                }
            }
        }
    }
    
    
    //run bipartite
    bipartiteMatch(aidx, bidx);
    
    // calculate Max independent set;
    calcMaxIndependentSet(aidx, bidx);
    
	// set board
    setRes(aidx, bidx);
	
	//reset
	for(int i = 0; i < aidx;i++)
		adj[i].clear();
}


void input(){
    cin>>H>>W;
    board = vector< vector<int> > (H, vector<int> (W,0));
    
    string tmp;
    for(int i = 0 ; i < H; i++){
        cin>>tmp;
        for(int j = 0; j < W; j++){
            board[i][j] = tmp[j] == '#' ? 0 : 1;
        }
    }
}

void output(){
    cout<<num_trap<<endl;
    for(int i = 0;  i < H; i++){
        for(int j = 0; j < W; j++){
            if( res[i][j] == 0) cout<<"#";
            else if (res[i][j] == 1) cout<<".";
            else cout<<"^";
        }
        cout<<endl;
    }
}



void solve(){
    input();
#ifdef DEBUG_INPUT
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
#endif
	
    //reset
    num_trap = 0;
    res = board;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if( board[i][j] == 1){
                //run bfs and find max independent set
                fillres(i,j);
            }
        }
    }

    output();
}


int main(){
    int c; cin>>c; while(c--) solve();
    return 0;
}