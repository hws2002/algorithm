#include <iostream>

#define MAX_N 1'000
#define MOD 1'000'000'003
using namespace std;


int N,K;
int cache[MAX_N][MAX_N+1][2] = {0};

int dp(const int idx, const int tochoose, bool taken0){
    //base 1
    if(tochoose == 1){
        if(taken0) return max(0,N-idx-1);
        return N-idx;
    }
    
    //base 2
    if(2*tochoose - 1 > (N-idx)) return 0;
    
    int & ret = cache[idx][tochoose][taken0];
    if(ret) return ret;
    if(idx == 0){
        return ret = (dp(idx+2, tochoose-1, true) + dp(idx+1, tochoose, false)) % MOD;
    } else {
        return ret = (dp(idx+2, tochoose-1, taken0) + dp(idx+1, tochoose, taken0)) % MOD;
    }
}

int main(){
    cin>>N>>K;
    if(K > N/2) {cout<<0<<endl; return 0;}
    cout<<dp(0,K,false)<<endl;
    return 0;
}