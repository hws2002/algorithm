#include <iostream>

#define MAX_K 1'000'000'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'

// #define DEBUG_SOLVE
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll K,C;

pll EEA(ll a, ll b){
    ll q = a / b; ll c = a % b;
    ll a1 = 0; ll b1 = 1;
    ll a2 = 1; ll b2 = -q;
    while(true){
        a = b; b = c;
        q = a / b; c = a % b;
        if( !c ) break;
        ll temp1 = a2; ll temp2 = b2;
        a2 = a1 - q*a2; b2 = b1 - q*b2;
        a1 = temp1; b1 = temp2;
    }
    return {a2,b2};
}

ll gcd(ll a, ll b){
    if( b > a ) swap(a,b);
    ll c = a % b;
    while(c){
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}

void solve(){
    cin>>K>>C;
    
    if( C == 1) {
        if(K+1 > MAX_K) cout<<"IMPOSSIBLE"<<endl;
        else cout<<K+1<<endl;
        return ;
    }
    
    if( K == 1){
        cout<<C-1<<endl;
        return ;
    }
    
    if(gcd(K,C) != 1){
        cout<<"IMPOSSIBLE \n";
        return ;
    }
    
    
    // KX + 1 = CY
    // -> solve CY + K(X_) = 1
    ll Y, X_;
    if( C >= K){
        // solution.first should be positive and solution.second should be negative
        auto solution = EEA(C,K);
        Y = solution.first; X_ = solution.second;
    } else {
        // solution.first should be negative and solution.second should be positive
        auto solution = EEA(K,C);
        X_ = solution.first; Y = solution.second;
    }
#ifdef DEBUG_SOLVE
    printf("Y, X_ : %lld %lld \n", Y, X_);
#endif
    while( Y <= 0) {
        Y += K;
        X_ -= C;
    }
    
    ll t = max( X_/C, (-Y)/K);
#ifdef DEBUG_SOLVE
    printf("X_/C, (-Y)/K : %lld, %lld \n", X_/C, (-Y)/K);
#endif
    // Y should be geq 1, X_ should be leq -1
    // 왜 이게 없어도 통과되지...?
    // if( Y + K*t == 0 || X_ - C*t == 0) t++;
    if( Y + K*t > MAX_K) cout<<"IMPOSSIBLE"<<endl;
    else cout<<Y + K*t<<endl;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}