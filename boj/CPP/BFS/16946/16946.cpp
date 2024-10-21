#include <iostream>
#include <queue>
#include <cstring>

#define MAX_N 1'000
#define MOD 10
#define endl '\n'
using namespace std;

int N,M;

int MAP[MAX_N][MAX_N] = {0};
bool V[MAX_N][MAX_N] = {0};

void bfs(int x, int y){
    int area = 0;
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,1,-1};
    
    typedef pair<int,int> pii;
    queue<pii> q;
    vector<pii> boundary;
    q.push({x,y});
    area++;
    MAP[x][y] = -1;
    while(!q.empty()){
        auto f = q.front(); q.pop();
        x = f.first; y = f.second;
        for(int i = 0; i < 4; i++){
            int nx = x+dx[i]; int ny = y + dy[i];
            if( 0 <= nx && nx < N && 0 <= ny && ny < M){
                if(MAP[nx][ny] == 0){
                    q.push({nx,ny});
                    area++;
                    MAP[nx][ny] = -1;
                } else if (MAP[nx][ny] > 0){ // wall
                    boundary.push_back({nx,ny});
                } else { // MAP[nx][ny] == -1 <=> already visited
                    //do nothing (continue)
                }
            }
        }
    }
    
    // printf("area : %d \n", area);
    
    for(auto b : boundary){
        if(!V[b.first][b.second]){
            MAP[b.first][b.second] = (MAP[b.first][b.second] + area);
            V[b.first][b.second] = true;
        }
    }
    for(auto b : boundary)
        V[b.first][b.second] = false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    string t;
    for(int i = 0 ; i < N; i++){
        cin>>t;
        for(int j = 0; j < M; j++){
            MAP[i][j] = t[j] - '0';
        }
    }
    
    //bfs
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < M; j++){
            if(MAP[i][j] == 0){
                // printf("bfs(%d,%d) \n", i, j);
                bfs(i,j);
            }
        }
    }
    
    for(int i = 0; i <N; i++){
        for(int j = 0; j < M; j++){
            if(MAP[i][j] == -1) cout<<0;
            else cout<<MAP[i][j]%MOD;
        }
        cout<<endl;
    }
    return 0;
}