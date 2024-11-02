#include <iostream>
#define MOD 1000000000
#define endl '\n'
typedef long long ll;

using namespace std;

ll STEP_NUM[11][101] = {0};
// STEP_NUM[start][length] : number of step number which starts with `start` and total length of `length`



ll dp(const int i, const int N){
    if( i < 0 || i > 9) return 0;
    if(STEP_NUM[i][N]) return STEP_NUM[i][N] % MOD;
    STEP_NUM[i][N] = (dp(i-1,N-1) + dp(i+1,N-1)) % MOD;
    return STEP_NUM[i][N] % MOD;
}


int main(){
    //input
    int N;
    cin>>N; // 1<= N <= 100
    
    //solve
    
    //base
    for(int i = 0 ; i <=9; i++){
        STEP_NUM[i][1] = 1;
    }

    ll res = 0;
    for(int i = 1; i <= 9; i++){
        res += dp(i,N);
        res %= MOD;
    }
    cout<<res<<endl;
    return 0;
}
