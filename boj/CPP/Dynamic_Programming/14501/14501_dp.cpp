#include <iostream>

using namespace std;

int N;
int T[16] = {0};
int P[16] = {0};
int dp[16] = {0};

int main(){
    //input
    cin>>N;
    for(int i = 1 ; i <= N; i++){
        cin>>T[i]>>P[i];
    }
    
    //solve
    if(T[N] == 1) dp[N] = P[N];
    
    for(int i = N-1; i>=1 ; i--){
        if(T[i] + i - 1 > N) dp[i] = dp[i+1];
        else dp[i] = max(dp[i+1], P[i] + dp[i + T[i]]);
    }
    
    cout<<dp[1]<<endl;
    return 0;
}

