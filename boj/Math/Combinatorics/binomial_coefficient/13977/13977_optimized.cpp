// 페르마 소정리 + non-recursive function
#include <iostream>

#define MAX_N 4'000'000
#define MOD 1'000'000'007
#define endl '\n'
using namespace std;
typedef long long ll;

int ncache[MAX_N+1] = {0}; // numerator cache
int dcache[MAX_N+1] = {0}; // denominator cache


ll powM(ll a, ll p){
	ll res = 1;
	while(p){
		if(p&1){
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
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

	return ( (ll)(((ll)ncache[n] * (ll)dcache[k]) % MOD) * (ll)dcache[n-k])% MOD;
}

void solve(){
	
	ll N,K;
	cin>>N>>K;
	cout<<nchooser(N,K)<<endl;
}

void calKfac(){
	ll fac = 1;
	ncache[1] = 1;
	for(ll i = 2; i <= MAX_N; i++){
		fac *= i;
		fac %= MOD;
		ncache[i] = (int)fac;
	}
}

void calKfacInverse(){
	dcache[MAX_N] = getinverse(ncache[MAX_N], MOD);
	for(ll i = MAX_N-1; i >= 1; i--){
		dcache[i] = (dcache[i+1] * (i+1)) % MOD;
	}
}

int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
	int M;
//pre
	calKfac();
	calKfacInverse();
	cin>>M;
	while(M--){
		solve();
	}
	
	return 0;
}