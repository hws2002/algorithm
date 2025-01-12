#include <iostream>
#include <cstring>
#include <vector>

#define MAX_N 64
using namespace std;
int N;
vector< vector<int> > board;

int coor2L[MAX_N][MAX_N] = {{-1}};
int coor2R[MAX_N][MAX_N] = {{-1}};
int lidx = 0; int ridx = 0;
vector<int> adj[MAX_N]; // adj[a] : a번째 left노드의 인접 right 노드들
vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

bool isOccupiedL(int x, int y){
    return coor2L[x][y] == -1;
}

bool isOccupiedR(int x, int y){
    return coor2R[x][y] == -1;
}

bool placable(int x, int y){
    if( 0 <= x && x < N && 0 <= y && y < N) return board[x][y];
    return false;
}

bool dfs(int a){
    if( visited[a] ) return false;
    visited[a] = true;
    for(const auto & b : adj[a]){
        if( bMatch[b] == -1 || dfs(bMatch[b])){
            aMatch[a] = b;
            bMatch[b] = a;
            return true;
        }
    }
    return false;
}

int bipartiteMatch(){
    aMatch = vector<int> (lidx, -1);
    bMatch = vector<int> (ridx, -1);
    int ret = 0;
    for(int i = 0; i < lidx; i++){
        visited = vector<bool> (lidx , false);
        if(dfs(i)) ret++;
    }
    return ret;
}

void solve(){
    cin>>N;
    string row;
    board = vector<vector<int>>(N, vector<int>(N,-1));
    for(int i = 0 ; i <N; i++){
        cin>>row;
        for(int j = 0; j < N; j++){
            board[i][j] = row[j] == '*' ? 0 : 1;
        }
        //reset
        fill(coor2L[i], coor2L[i] + N, -1);
        fill(coor2R[i], coor2R[i] + N, -1);
    }
    
    //create bipartite-graph
    lidx = 0; ridx = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if( placable(i,j)){
                if( !isOccupiedL(i,j)){ // create leftNode
                    int x1 = i; int y1 = j;
                    while( placable(x1+1,y1-1)){
                        x1++; y1--;
                        coor2L[x1][y1] = lidx;
                    }
                    coor2L[i][j] = lidx++;
                }
                
                if( !isOccupiedR(i,j)){//create rightNode
                    int x1 = i; int y1 = j;
                    while( placable(x1+1, y1+1) ){
                        x1++; y1++;
                        coor2R[x1][y1] = ridx;
                    }
                    coor2R[i][j] = ridx++;
                }
                
                adj[coor2L[i][j]].push_back( coor2R[i][j] );
            }
        }
    }
    
    //bipartiteMatch
    cout<<bipartiteMatch()<<endl;
}

int main(){
    int C; cin>>C; while(C--) solve();
    return 0;
}
