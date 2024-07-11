#include <iostream>

#define MAX_N 1'000
#define MOD 1'000'000'003
using namespace std;


int N,K;
int cache[MAX_N][MAX_N/2+1] = {0};

int dp(int n, int tochoose){
    //base
    if(tochoose == 1) return max(0,n);
    if(2*tochoose-1 > n || tochoose <= 0 || n <= 0) return 0;
    int & ret = cache[n][tochoose];
    if(ret) return ret;
    return ret = (dp(n-2, tochoose-1) + dp(n-1, tochoose)) % MOD;
}

int main(){
    cin>>N>>K;
    if(K > N/2) {cout<<0<<endl; return 0;}
    if(K == 1) {cout<<N<<endl; return 0;}
    cout<<(dp(N-1,K) + dp(N-3,K-1)) % MOD<<endl;
    return 0;
}