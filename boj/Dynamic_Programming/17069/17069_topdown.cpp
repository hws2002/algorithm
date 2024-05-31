
// dp - topdown

/*
dp(state, x * 18 + y) : "맨처음 시작 지점( 0, (1, 1)) 에서 (state, (x,y))에 도달하기 까지의 방법의 수 "
로 정의하면 optimal structure를 만족시킨다.  
dp(state, x * 18 + y) = 
1) state == 0 (horizontal)
dp(0, x * 18 + y - 1) + dp(2, x * 18 + y-1)
2) state == 1 (vertical) 
dp(1, (x-1) * 18 + y) + dp(2, (x-1)*18 + y)
3) state == 2 (diagonal)
dp(0, (x-1)*18 + y-1) + dp(1, (x-1)*18 + y-1) + dp(2, (x-1)*18 + y-1)

이 되므로, memoization만 잘 적용하면 끝!
*/

// 1 : 빈칸
// 0 : 벽
#include <iostream>
#include <algorithm>

#define NUM_STATE 3
#define MAX_N 34
typedef long long ll;
using namespace std;

typedef enum {
    HORI, // horizontal
    VERT, // vertical
    DIAG // diagonal
} State;

int N;
bool MAP[MAX_N][MAX_N] = {false};

// cache는 -1로 초기화한다
ll cache[NUM_STATE][MAX_N][MAX_N];

ll dp(State state, int x, int y){ //TODO
    ll& ret = cache[state][x][y];
    if(ret > -1) return ret;
	
	ret = 0;
	//base1
	if( x <= 2 && state == VERT) return ret;
	//base2
	if( x < 1 || y <= 2) return ret;
	
	if(state == HORI){
        if(MAP[x][y-1] && MAP[x][y-2]){
			ret += dp(HORI, x, y-1);
			if(MAP[x-1][y-1] && MAP[x-1][y-2]){
				ret += dp(DIAG, x , y-1);
			}
		}
    } else if (state == VERT){
        if(MAP[x-1][y] && MAP[x-2][y]){
			ret += dp(VERT, x-1, y );
			if(MAP[x-1][y-1] && MAP[x-2][y-1]){
				ret += dp(DIAG, x-1, y);
			}
		}
    } else { // diag
		
        if(MAP[x-1][y] && MAP[x][y-1] && MAP[x-1][y-1] && MAP[x-1][y-2]){
			ret += dp(HORI, x-1, y-1);
		}
	
        if(MAP[x-1][y] && MAP[x][y-1] && MAP[x-1][y-1] && MAP[x-2][y-1]){
			ret += dp(VERT, x-1, y-1);
		}

		if(MAP[x-1][y] && MAP[x][y-1] && MAP[x-1][y-1] && MAP[x-1][y-2] && MAP[x-2][y-1] && MAP[x-2][y-2]){
			ret += dp(DIAG, x-1, y-1);
		}
	}
	return ret;
}

int main(){
    
    for(int i = 0 ; i < NUM_STATE; i++){
		for(int j = 0; j < MAX_N; j++){
	        std::fill(cache[i][j], cache[i][j] + MAX_N, -1);		
		}
    }
    cache[HORI][1][2] = 1;
	
    cin>>N;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin>>MAP[i][j];
            MAP[i][j] = !MAP[i][j];
        }
    }
    
    //solve - dp
    //caculate number of routes 
	if(MAP[N][N] == 0) cout<<0<<endl;
    else cout<<dp(HORI, N , N) + dp(VERT, N , N) + dp(DIAG,N , N)<<endl;
    return 0;
}