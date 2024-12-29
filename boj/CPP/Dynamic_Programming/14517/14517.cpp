#include <iostream>
#include <cstring>
#include <vector>

#define MOD 10'007
#define MAX_N 1'000

using namespace std;

string S;
int N;

int cache[MAX_N][MAX_N] = {{0}};

int dp(int s, int e){
    if( s >= N || e < 0 || s > e) return 0;
    if( e == s) return cache[s][e] = 1;
    
    int & ret = cache[s][e];
    if(ret) return ret;
    
    if(S[s] == S[e])
        return ret = (dp(s+1,e) + dp(s,e-1) + 1) % MOD;
    else 
        return ret = (dp(s+1,e) + dp(s,e-1) - dp(s+1, e-1) + MOD) % MOD;
        
    return ret % MOD;
}

int main(){
    cin>>S;
    //base
    N = S.size();
    cout<<dp(0,N-1)%MOD<<endl;
    return 0;
}