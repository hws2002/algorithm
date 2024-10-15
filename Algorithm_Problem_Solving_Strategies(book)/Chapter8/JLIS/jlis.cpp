#include <iostream>
#include <vector>
#include <limits>

#define MAX_N 101
#define endl '\n'
using namespace std;
typedef long long ll;

int n,m;
vector<ll> A;
vector<ll> B;

ll cache[MAX_N][MAX_N] = {0};

ll dp(int ai, int bi){
    //base
    if(ai >= n && bi >= m) return 0;

    ll & ret = cache[ai][bi];
    if(ret) return ret;

    ll largest = max(A[ai], B[bi]);
    for(int i = ai+1;  i <= n; i++){
        if( largest < A[i])
            ret = max<ll>(ret, 1 + dp(i, bi));
    }

    for(int j = bi+1; j <= m; j++){
        if ( largest < B[j])
            ret = max<ll>(ret, 1 + dp(ai, j));
    }

    return ret;
}

void solve(){
    cin>>n>>m;
    //reset
    for(int i = 0; i <= n; i++){
        fill(cache[i], cache[i] + m + 1, 0);
    }
    
    A.resize(n+1);
    A[0] = numeric_limits<ll>::min();
    for(int i = 1; i <= n; i++){
        cin>>A[i];
    }
    
    B.resize(m+1);
    B[0] = numeric_limits<ll>::min();
    for(int i = 1; i <= m; i++){
        cin>>B[i];
    }
    
    cout<<dp(0,0)<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}