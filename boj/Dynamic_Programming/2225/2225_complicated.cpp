#include <iostream>
#define MOD 1000000000
#define endl '\n'
#define DEBUG_CHOOOSE
typedef long long ll;

using namespace std;

ll CHOOSE[201][201];

ll choose(const int & n, const int & r){
    if (r == 0 || r == n) return 1;
    if (r == 1 || r == n-1) return n;
    if (CHOOSE[n][r] || CHOOSE[n][n-r]) return CHOOSE[n][r] % MOD;
    ll res = 0;
    res = choose(n-1,r) % MOD + choose(n-1,r-1) % MOD;
    res %= MOD;
    CHOOSE[n][r] = res; CHOOSE[n][n-r] = res;
#ifdef DEBUG_CHOOOSE
cout<<n<<" choose "<<r<<" : "<<res<<endl;
#endif
    return res;
}

ll dp(int n, int k){
    ll res = 0;
    for(int i = 1; i <= min(n,k); i++){
        res += ( choose(n-1, n-i) * choose(k, i)) % MOD;
    }
    return res % MOD;
}

int main(){
    //input
    int N,K;
    cin>>N>>K;
    if( K == 1){
        cout<<1<<endl;
        return 0;
    }
    if( N == 1){
        cout<<K<<endl;
        return 0;
    }

    //solve
    cout<<dp(N,K)<<endl;
    return 0;
}