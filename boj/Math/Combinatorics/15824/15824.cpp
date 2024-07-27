#include <iostream>
#include <vector>
#include <algorithm>

#define MOD (ll) 1'000'000'007
#define MAX_N 300'000
#define endl '\n'
// #define DEBUG_SOLVE
typedef long long ll;
using namespace std;

ll cache[MAX_N] = {0};

ll pow2(int p){
    if( p <= 0 ) return 1;
    if( p < MAX_N){
    ll& ret = cache[p];
    if(ret) return ret;
    if( p % 2) return ret = (2 * pow2(p-1)) % MOD;
    return ret = (pow2(p/2) * pow2(p/2)) % MOD;
    } else {
        if( p % 2 ) return (2 * pow2(p-1)) % MOD;
        return (pow2(p/2) * pow2(p/2) ) % MOD;
    }
}

ll inverse2 = 0;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    inverse2 = pow2(MOD-2);
    int n;
    cin>>n;
    vector<ll> foods(n);
    for(int i = 0; i < n; i++){
        cin>>foods[i];
    }
    
    std::sort(foods.begin(), foods.end());
    ll res = 0;
    // 첫번째 조합은 그냥 계산한다
    ll l;
    ll s = foods[0];
    ll toadd = 0;
    for(int j = n-1; j > 0; j--){
        l = foods[j];
        toadd += ( (l-s) * pow2(j-1)) % MOD;
        toadd %= MOD;
    }
    res += toadd;
    res %= MOD;
#ifdef DEBUG_SOLVE
cout<<"toadd : "<<toadd<<endl;
#endif
    for(int i = 1 ; i < n-1; i++){
        int length = n - i;
        toadd += (ll)10*MOD;
        toadd -= ( (foods[i] - foods[i-1]) % MOD * (pow2(length)-1)) % MOD;
        toadd %= MOD;
        toadd *= inverse2;
        toadd %= MOD;
#ifdef DEBUG_SOLVE
cout<<"toadd : "<<toadd<<endl;
#endif
        res += toadd;
        res %= MOD;
    }
    cout<<res<<endl;
    return 0;   
}