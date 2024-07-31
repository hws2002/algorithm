#include <iostream>

#define MAX_N 1'000
#define INF (-2'000'000'000)
// #define DEBUG_DP
using namespace std;

int N,M;
int MAP[MAX_N][MAX_N] = {0};
int cache[MAX_N][MAX_N][3] = {0};

int dx[3] = {0,0,1};
int dy[3] = {-1,1,0};

// dp(r,c,d) : d번째 방향을 통해서 (r,c)로 도착했고, (r,c)좌표에서 시작했을때 얻을 수 있는 최대 가치의 합을 출력한다.
// * 1번째 방향(0) : 왼쪽
//   2번째 방향(1) : 오른쪽
//   3번째 방향(2) : 아래쪽

const bool returning(const int i, const int d){
    if(d == 0 && i == 1) return true;
    if(d == 1 && i == 0) return true;
    return false;
}

// const int nextd(const int i){
//     if(i == 0) return 1;
//     if(i == 1) return 0;
//     else return 2;
// }

// int cnt = 0;
int dp(const int r, const int c, const int d){
    //base

    // 끝에 도달했을때
    if( r == N-1 && c == M-1) return MAP[r][c];
    if( r >= N || c >= M) return INF;
	
    // 끝에 도달하지 못할때
    if( d == 0 && r >= N-1) return INF;
    
    int & ret = cache[r][c][d];
    if(ret > INF) return ret;
	// if(cnt++ < 10) printf("dp(%d,%d,%d) \n",r,c,d);
    
    for(int i = 0; i < 3; i++){
        int nx = r + dx[i]; int ny = c + dy[i];
        
        // 탐사지역만 고려한다
        if( !(0 <= nx && nx < N && 0 <= ny && ny < M ) ) continue;
        
        // 방금 왔던 지역은 고려하지 않는다.
        if (returning(i,d)) continue;
		
        // ret = max( ret, dp(nx,ny, nextd(i)));
		ret = max( ret, dp(nx,ny,i) );
    }
    
    // if(ret == INF) return ret = INF-1;
    return ret += MAP[r][c];
}

int main(){
    cin>>N>>M;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin>>MAP[i][j];
        }
    }
    
    //pre
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			for(int k = 0; k < 3; k++)
				cache[i][j][k] = INF;
		}
	}
    cout<<dp(0,0,1)<<endl;

#ifdef DEBUG_DP
for(int i = 0; i < 3; i++){
	for(int j = 0 ; j < N; j++){
		for(int k = 0; k < M;k ++){
			cout<<cache[j][k][i]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
#endif
    return 0;
}