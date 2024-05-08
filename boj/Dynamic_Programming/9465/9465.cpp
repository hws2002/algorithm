#include <cstdio>
#include <cstring>
#include <limits.h>
#include <cmath>
// #define DEBUG_INPUT
// #define DEBUG_DP

using namespace std;



int N;
int MAP[2][100002] = {0};
int RES[3][100002] = {0};

#ifdef DEBUG_INPUT
void printMAP(){
    for(int i = 0 ; i < 2; i++){
        for(int j = 0 ; j < N; j++){
            cout<<MAP[i][j]<<" ";
        }
        printf("\n");
    }
}
#endif

int dp(const int r, const int c){
    if(c >= N) return 0; 
    if( RES[r][c] ) return RES[r][c];
    int res = 0;
    if( r == 0){
        res = max( dp(0, c+1) , max(MAP[0][c] + dp(2,c+1) , MAP[1][c] + dp(1, c+1)) );
    } else  if( r == 1 ){
        res = max( dp(0, c+1) , MAP[0][c] + dp(2,c+1) );
    } else if( r == 2 ){
        res = max( dp(0, c+1) , MAP[1][c] + dp(1,c+1) );
    } 
    RES[r][c] = res;
#ifdef DEBUG_DP
cout<<"RES["<<r<<"]["<<c<<"] : "<< res<<endl;
#endif
    return res;
}

void solve(){
    scanf("%d",&N);
    for(int i = 0 ; i < 2; i++){
        for(int j = 0 ; j < N; j++){
            scanf("%d", &MAP[i][j]);
        }
    }
#ifdef DEBUG_INPUT
printMAP();
#endif
    printf("%d \n",dp(0,0));
    
    // reset RES
    for(int i = 0 ; i < 3; i++){
        // std::fill(RES[i] , RES[i] + N, 0);
        memset(RES[i], 0, N * sizeof(int));
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}