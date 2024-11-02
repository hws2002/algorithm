#include <iostream>

#define MAX_P 54LL
// #define DEBUG_G
using namespace std;
typedef long long ll;

// // 5 -> return 3 (2^2 = 4)
// // 4 -> return 2
ll log2floor(ll n){
    ll ret = 0;
    while( n >= 1LL<<ret) {
        // printf("ret, val : %lld, %lld \n", ret, ll(1)<<ret);
        ret++;
    }
    return ret;
}

ll G[MAX_P+1] = {0};
// F[i] = G[i] + 1;

ll getF(ll n){
    // printf("getF(%lld) ", n);
    if( n==0 ) return 0;
    
    ll num1 = 0;
    ll ret = 0;
    ll d = log2floor(n);
    // printf(" d : %lld \n", d);

    for(int i = d-1LL; i >= 0 && n; i--){
        if( n & (1LL<<i) ){
            ret += num1*(1LL<<i) + (G[i] + 1LL);
            num1++;
        }
        n &= ~(1LL<<i);
    }

    // printf("ret : %lld \n", ret);
    return ret;
}

ll a,b;
int main(){
    // scanf("%lld %lld", &a, &b);
    cin>>a>>b;

    G[0] = 0;
    for(ll i = 1LL; i <= MAX_P; i++){
        G[(int)i] = G[(int)i-1] + (1LL<<(i-1LL));
        G[(int)i] += G[(int)i-1];
    }

    #ifdef DEBUG_G
    for(int i = 0 ; i <= MAX_P; i++){
        printf("G[%d] : %lld \n", i, G[i]);
    }
    #endif
    cout<<getF(b) - getF(a-1LL)<<endl;
    return 0;
}