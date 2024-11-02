#include <iostream>

#define MAX_N 500
using namespace std;

int N,M;
int MAP[MAX_N][MAX_N] = {0};

int cache[MAX_N][MAX_N] = {-1};

int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};

int dp(int r, int c){
    //base
    if(r >= M || c >= N) return 0;
    if(r == M-1 && c == N-1) return 1;
	
	int & ret = cache[r][c];
    if(ret > -1) return ret;
    ret = 0;
    
    for(int i = 0; i < 4; i++){
        if(0 <= r + dx[i] && r + dx[i] < M && 0 <= c + dy[i] && c + dy[i] < N){
            if( MAP[r][c] > MAP[r + dx[i]][c + dy[i]] ){
                ret += dp(r+dx[i], c + dy[i]);
            }
        }
    }
    return ret;
}

int main(){
    cin>>M>>N;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            cin>>MAP[i][j];
        }
    }
    
    
    //solve
    //pre
    for(int i = 0; i < M; i++){
        fill(cache[i], cache[i] + N, -1);
    }
    cout<<dp(0,0)<<endl;
    
    return 0;
}