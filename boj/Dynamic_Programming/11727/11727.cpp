#include <iostream>
#define MOD 10007
#define endl '\n'

using namespace std;

int RES[1001] = {0};

int dp(const int & n){
    if(n == 0 | n==1) return n;
    if(n == 2) return 3;
    if(RES[n]) return RES[n];
    int res = (dp(n-1) + 2 * dp(n-2))%MOD;
    RES[n] = res;
    return res % MOD;
}

int main(){
    //input
    int n;
    cin>>n;
	
    //solve
    cout<<dp(n) % MOD<<endl;    
    return 0;
}