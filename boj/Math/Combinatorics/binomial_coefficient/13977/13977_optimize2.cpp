// 페르마 소정리 + non-recursive function
#include <iostream>

#define MAX_N 4'000'000
#define MOD (ll)1'000'000'007
#define endl '\n'
using namespace std;
typedef long long ll;

ll ncache[MAX_N+1] = {0}; // numerator cache
ll inv[MAX_N+1] = {0};
ll dcache[MAX_N+1] = {0}; // denominator cache


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


void init(){
	dcache[1] = 1;
	inv[1] = 1;
	ncache[1] = 1;
	for(ll i = 2; i <= MAX_N; i++){
		ncache[i] = ncache[i-1] * i % MOD;
		inv[i] =  ( (MOD-(MOD/i) ) * inv[MOD%i]) % MOD;
		dcache[i] = ((dcache[i-1] * inv[i]) % MOD);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int M;
//pre
	init();
	cin>>M;
	while(M--){
		solve();
	}
	
	return 0;
}