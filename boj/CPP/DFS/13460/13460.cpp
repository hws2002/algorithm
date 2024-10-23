#include <iostream>
#include <cstring>

// #define DEBUG_DFS
#define MAX_N 11
using namespace std;

int N,M;
int MAP[MAX_N][MAX_N] = {0};
int ox,oy;

int ret = 11;

void dfs(int rx_, int ry_, int bx_, int by_, int d, string path){
    if(d >= ret-1) return ;
#ifdef DEBUG_DFS
printf("dfs(%d,%d,%d,%d,%d) with path : ", rx_, ry_, bx_, by_, d);
	cout<<path<<endl;
for(int i = 0; i< N; i++){
	for(int j = 0; j < M; j++){
		cout<<MAP[i][j];
	}
	cout<<endl;
}
#endif

    for(int i = 0 ; i < 4; i++){
        int rx = rx_; int ry = ry_; int bx = bx_; int by = by_;
		bool bfell = false; bool afell = false; bool godfs = false;
        if( i == 0){ //up
            bool redmoved = false;
            // blue 먼저 움직인다
            for(int r = bx; r >= 0; r--){
                if( MAP[r][by] == 4) { // blue가 구멍에 빠진다면
					bfell = true;	
					break;
					// return ;
				}
				if( MAP[r][by] == 2){ // red를 만난다면
                    //red를 움직이고 그 바로 아래에 blue를 둔다
                    for(int r2 = rx; r2 >= 0; r2--){
                        if( MAP[r2][ry] == 4) {// 구멍을 만난다면, blue 와 red가 동시에 빠지므로, 바로종료한다
							bfell = true; afell = true;
                            break;
                        }

                        if( MAP[r2][ry] == 0){ // 벽을 만난다면
                            rx = r2+1; bx = rx+1;
                            MAP[rx][ry] = 2; //mark as red
                            MAP[bx][by] = 3; //mark as blue
							if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
							if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                            break;
                        }
                    }
                    redmoved = true;
                    break;
                } else if( MAP[r][by] == 0){ // 벽에 만난다면
                    bx = r+1;
                    MAP[bx][by] = 3; // mark as blue
					if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
                    break;
                }
            }
			
			if(bfell ) {// blue가 빠졌다면 다음 depth로 넘어가지 않는다
				// MAP원복은 진행한다
				MAP[rx][ry] = 1; MAP[bx][by] = 1;
				MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
				continue;
			}
			
			// 빠지지않았고, red가 아직 움직이지 않았다면
            if(!redmoved){
                //red를 움직인다
                for(int r = rx; r >= 0; r--){
                    if( MAP[r][ry] == 4) { // 구멍에 빠진다면
						afell = true;
#ifdef DEBUG_DFS
printf("found new candid! %d \n", d+1);
#endif
						ret = min(ret, d+1);
						//원복 까먹지 않기!
						MAP[rx][ry] = 1; MAP[bx][by] = 1;
						MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
                        return ;
                    }
                    if( MAP[r][ry] == 3 || MAP[r][ry] == 0){ // blue나 벽을 만난다면
                        rx = r+1;
                        MAP[rx][ry] = 2; // mark as red
						if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                        break;
                    }
                }
            }

			// red 가 움직인 후 구멍에 빠졌다면 이미 return했으므로, 
			// 이경우는 red도 구멍에 빠지지 않은 상황이다.
		    if(godfs) dfs(rx,ry,bx,by,d+1, path + string("u"));
			MAP[rx][ry] = 1; MAP[bx][by] = 1;
			MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
        } else if ( i == 1){ // left
            bool redmoved = false;
            for(int c = by; c >= 0 ;c--){
                if( MAP[bx][c] == 4){ // meet hole
 					bfell = true;
					break;
                }
				
                if( MAP[bx][c] == 2){ // meet red
                   for(int c2 = ry; c2 >= 0; c2--){
                        if( MAP[rx][c2] == 4){
							afell = true; bfell = true;
							break;
                            // ret = min(ret, d+1);
                            // return ;
                        }
                        if( MAP[rx][c2] == 0){
                            ry = c2 + 1; by = ry+1;
                            MAP[rx][ry] = 2;
                            MAP[bx][by] = 3;
							if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
							if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
                            break;
                        }
                    }
					redmoved = true;
					break;
                } else if (MAP[bx][c] == 0){
                    by = c+1;
                    MAP[bx][by] = 3;
					if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
                    break;
                }
            }
            
			if(bfell) {
				MAP[rx][ry] = 1; MAP[bx][by] = 1;
				MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
				continue;
			}
			
            if(!redmoved){
                for(int c = ry; c >= 0; c--){
                    if( MAP[rx][c] == 4){
#ifdef DEBUG_DFS
printf("found new candid! %d \n", d+1);
#endif
                        ret = min(ret, d+1);
						MAP[rx][ry] = 1; MAP[bx][by] = 1;
						MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
                        return;
                    }
                    if( MAP[rx][c] == 3 || MAP[rx][c] == 0){
                        ry = c+1;
            	        MAP[rx][ry] = 2;
						if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                        break;
                    }
                }
            }
		    if(godfs) dfs(rx,ry,bx,by,d+1, path + string("l"));
			MAP[rx][ry] = 1; MAP[bx][by] = 1;
			MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
        } else if (i == 2){ // down
            bool redmoved = false;
            // blue 먼저 움직인다
            for(int r = bx; r < N; r++){
                if( MAP[r][by] == 4) {
					bfell = true;
					break;
				}
                if( MAP[r][by] == 2){ // red를 만난다면
                    //red를 움직이고 그 바로 위에 blue를 둔다
                    for(int r2 = rx; r2 < N; r2++){
                        if( MAP[r2][ry] == 4) {
							afell = true;
							bfell = true;
                            // ret = min(ret, d+1);
                            // return ;
							break;
                        }
                        if( MAP[r2][ry] == 0){ // 벽을 만난다면
                            rx = r2-1; bx = rx-1;
                            MAP[rx][ry] = 2; //mark as red
                            MAP[bx][by] = 3; //mark as blue
							if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
							if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                            break;
                        }
                    }
                    redmoved = true;
                    break;
                } else if( MAP[r][by] == 0){ // 벽을 만난다면
                    bx = r-1;
                    MAP[bx][by] = 3; // mark as blue
					if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
                    break;
                }
            }
			
			if(bfell) {
			MAP[rx][ry] = 1; MAP[bx][by] = 1;
			MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
				continue;
			}
            if(!redmoved){
                //red를 움직인다
                for(int r = rx; r < N; r++){
                    if( MAP[r][ry] == 4) {
#ifdef DEBUG_DFS
printf("found new candid ! %d \n", d+1);
#endif
                        ret = min(ret, d+1);
						MAP[rx][ry] = 1; MAP[bx][by] = 1;
						MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
                        return ;
                    }
                    if( MAP[r][ry] == 3 || MAP[r][ry] == 0){ // blue나 벽을 만난다면
                        rx = r-1;
                        MAP[rx][ry] = 2; // mark as red
						if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                        break;
                    }
                }
            }
			
		    if(godfs) dfs(rx,ry,bx,by,d+1, path + string("d"));
			MAP[rx][ry] = 1; MAP[bx][by] = 1;
			MAP[rx_][ry_] = 2;
			MAP[bx_][by_] = 3;
        } else { // right
            bool redmoved = false;
            for(int c = by; c < M ; c++){
                if( MAP[bx][c] == 4){
					bfell = true;
					break;
                }
				
                if( MAP[bx][c] == 2){ // meet red
                    for(int c2 = ry; c2 < M; c2++){
                        if( MAP[rx][c2] == 4){
							afell = true; bfell = true;
							break;
                        }
                        
                        if( MAP[rx][c2] == 0 ){
                            ry = c2-1; by = ry-1;
                            MAP[rx][ry] = 2;
                            MAP[bx][by] = 3;
							if(bx != bx_ || by != by_) {MAP[bx_][by_] = 1; godfs = true;}
							if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                            break;
                        }
                    }

                    redmoved = true;
					break;
                } else if (MAP[bx][c] == 0){
                    by = c-1;
                    MAP[bx][by] = 3;
					if(bx != bx_ || by != by_) {
						MAP[bx_][by_] = 1; godfs = true;
					}
                    break;
                }
            }
            
            if(bfell) {
				MAP[rx][ry] = 1; MAP[bx][by] = 1;
				MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
				continue;
			}
			
			if(!redmoved){
                for(int c = ry; c < M; c++){
                    if( MAP[rx][c] == 4){
#ifdef DEBUG_DFS
printf("found new candid ! %d \n", d+1);
#endif
                        ret = min(ret, d+1);
						MAP[rx][ry] = 1; MAP[bx][by] = 1;
						MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
                        return;
                    }
                    if( MAP[rx][c] == 3 || MAP[rx][c] == 0){
                        ry = c-1;
                        MAP[rx][ry] = 2;
						if(rx != rx_ || ry != ry_) {MAP[rx_][ry_] = 1; godfs = true;}
                        break;
                    }
                }
            }
			
		    if(godfs) dfs(rx,ry,bx,by,d+1, path + string("r"));
			MAP[rx][ry] = 1; MAP[bx][by] = 1;
			MAP[rx_][ry_] = 2; MAP[bx_][by_] = 3;
        }
    }
}

int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);
    cin>>N>>M;
    string tmp;
    int rx,ry,bx,by;
    for(int i = 0; i < N; i++){
        cin>>tmp;
        for(int j = 0;  j < M; j++){
            if(tmp[j] == '#'){
                MAP[i][j] = 0;
            } else {
                MAP[i][j] = 1;
                if (tmp[j] == 'R'){
                    MAP[i][j] = 2;
                    rx = i; ry = j;
                } else if (tmp[j] == 'B'){
                    MAP[i][j] = 3;
                    bx = i; by = j;
                } else if (tmp[j] == 'O'){
                    MAP[i][j] = 4;
                    ox = i; oy = j;
                } else {
                    //do nothing
                }
            }
        }
    }
    
    dfs(rx,ry,bx,by,0, "");
    if(ret >= 11) cout<<-1<<endl;
    else cout<<ret<<endl;
    return 0;
}
