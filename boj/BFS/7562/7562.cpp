#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_I 300
#define NUM_DIRECTION 8
#define endl '\n'
using namespace std;

int dx[NUM_DIRECTION] = {-1,-2,-2,-1,1,2,2,1};
int dy[NUM_DIRECTION] = {-2,-1,1,2,-2,-1,1,2};

int I;

bool inBoard(int x, int y){
    if( 0 <= x && x < I && 0 <= y && y < I) return true;
    return false;
}

int bfs(int kx, int ky, const int tx, const int ty){
    int vcnt = 0;
    //trivial
    if (kx == tx && ky == ty) return vcnt;
    queue<int> q;
    int MAP[MAX_I][MAX_I] = {0};
    q.push( kx * MAX_I + ky);
    
    while(!q.empty()){
        kx = q.front() / MAX_I; ky = q.front() % MAX_I;
        q.pop();
        vcnt = MAP[kx][ky];
        for(int i = 0; i < NUM_DIRECTION; i++){
            int nx = kx + dx[i]; int ny = ky + dy[i];
            if( !inBoard(nx,ny) ) continue;
            if (nx == tx && ny == ty) return vcnt+1;
            if( !MAP[nx][ny] ){
                MAP[nx][ny] = vcnt+1;
                q.push(nx*MAX_I + ny);
            }
        }
    }
}



void solve(){
    cin>>I;
    int kx, ky; // knight_x, knight_y
    int tx, ty; // target_x, target_y
    cin>>kx>>ky;
    cin>>tx>>ty;
    cout<<bfs(kx,ky,tx,ty)<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}