// 페르마 소정리 + non-recursive function
#include <iostream>

#define MAX_N 4'000'000
#define MOD 1'000'000'007
using namespace std;
typedef long long ll;



ll powM(ll a, ll p){
	ll res = 1;
	ll tomul = a;
	while(p){
		if(p&1){
			res *= tomul;
			res %= MOD;
		}
		tomul *= tomul;
		tomul %= MOD;
		p>>=1;
	}
	return res;
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