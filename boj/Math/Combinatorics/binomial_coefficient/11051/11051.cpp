#include <iostream>

#define MOD 10007
#define MAX_N 1000
using namespace std;
typedef long long ll;

int N,K;

ll cache[MAX_N+1][(MAX_N>>1) + 1] = {0};

ll nchooser(int n, int k){
    //base
    if( k >= n || k <= 0 || n <= 1) return 1;
    if( k == 1) return n;
    
    if(n-k < k) return nchooser(n, n-k);
    
    ll& res = cache[n][k];
    if(res > 0 ) return res;
    res = 0;
    for(int i = 0 ; i <= k; i++){
        res += (nchooser(k,i) * nchooser(n-k, k-i)) % MOD;
        res %= MOD;
    }
    return res;
}    

int main(){
    cin>>N>>K;
    cout<<nchooser(N,K)<<endl;
    return 0;
}
