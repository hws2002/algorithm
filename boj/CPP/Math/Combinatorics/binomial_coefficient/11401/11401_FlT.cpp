// cache쓰지 않은 페르마 소정리 활용한 풀이
#include <iostream>

#define MAX_N 4'000'000
#define MOD 1'000'000'007
using namespace std;
typedef long long ll;

ll powM(ll a, ll p){
	//base
	if(p<=0) return 1;
	if(p==1) return a;
	if(p % 2) return (a * powM(a,p-1) ) % MOD;
	ll half = powM(a,p/2);
	return (half * half) % MOD;
}


ll getinverse(ll a, ll m){
	return powM(a,m-2);
}

ll nchooser(ll n, ll k){

	//base
	if(k <= 0 || k >= n || n <= 1) return 1;
	if(k == 1) return n;
	if(n-k < k ) return nchooser(n,n-k);
	
	ll ret = n;
	for(ll i = 1; i <= k-1;i++){
		ret *= (n-i);
		ret %= MOD;
	}
	
	for(ll i = 1; i <= k; i++){
		ret *= getinverse(i, MOD);
		ret %= MOD;
	}
	return ret;
}

int main(){
	ll N,K;
	cin>>N>>K;
	
	cout<<nchooser(N,K)<<endl;
	
	return 0;
}