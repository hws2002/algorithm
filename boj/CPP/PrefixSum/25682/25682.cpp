#include <iostream>
#include <limits.h>

#define MAX_N 2'000
// #define DEBUG_PREFIX
using namespace std;

int N,M,K;

//'B' : 0, 'W" : 1
bool MAP[MAX_N][MAX_N] = {0};
int preSum[MAX_N+1][MAX_N+1] = {0};

int main(){
    cin>>N>>M>>K;
    char c;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < M; j++){
           cin>>c;
           MAP[i][j] = c - 'B';
        }
    }
    
    //black
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1];
            if( MAP[i-1][j-1] != ( (i+j) % 2 ))
                preSum[i][j] += 1;
        }
    }
#ifdef DEBUG_PREFIX
for(int i = 0 ; i <= N; i++){
	for(int j = 0 ; j <= M; j++){
		cout<<preSum[i][j]<<" ";
	}
	cout<<endl;
}
#endif
    int res = INT_MAX;
    for(int i = 1; i+K-1 <= N; i++){
        for(int j = 1; j+K-1 <= M; j++){
            int tochange = preSum[i+K-1][j+K-1] - preSum[i-1][j+K-1] - preSum[i+K-1][j-1] + preSum[i-1][j-1];
            res = min(res, min(K*K- tochange, tochange));
        }
    }
    
    cout<<res<<endl;
    return 0;
    
}
