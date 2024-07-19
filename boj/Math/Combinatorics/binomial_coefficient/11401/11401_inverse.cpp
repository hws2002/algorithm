#include <iostream>

#define MOD 1'000'000'007
#define MAX_N 4'000'000
using namespace std;
typedef long long ll;

ll N,K;

ll cache[2'000'000] = {0};

ll EEA(ll a, ll b){// (a,b) = 1 , a > b 이 보장됨
	ll q = a / b; ll c = a % b;
	ll a1 = 0; ll b1 = 1;
	ll a2 = 1; ll b2 = -q;
	while(true){
		a = b; b = c;
		q = a / b; c = a % b;
		if(!c) break;
		ll temp1 = a2; ll temp2 = b2;
		a2 = a1 - q*a2; b2 = b1 - q*b2;
		a1 = temp1; b1 = temp2;
	}
	return b2;
}

//solve ax + py = 1
ll getinverse(ll a, ll p){ //
	if(a == 1) return 1;
	ll& ret = cache[a];
	if(ret) return ret;
	ret = EEA(p,a);
	while(ret<0) ret += p;
	ret %= p;
	return ret;
}

ll nchooser(ll n, ll k){
	//base
	if( k <= 0 || k >= n || n <= 1) return 1;
	if( k == 1) return n;
	if( n-k < k) return nchooser(n,n-k);

	ll ret = n;
	for(ll i = 1; i < k; i++){
		ret *= (n-i);
		ret %= MOD;
	}
	
	// printf("ret : %lld \n", ret);
	for(ll i = 1; i <= k; i++){
		// printf("getinverse(%d,%d) : %lld \n", i, MOD, getinverse(i,MOD));
		ret *= getinverse(i,MOD);
		ret %= MOD;
	}
	return ret;
}

int main(){
    cin>>N>>K;
    cout<<nchooser(N,K)<<endl;
    return 0;
}
