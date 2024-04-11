#include <iostream>
#define endl '\n'
#define MOD 1000000009
typedef long long ll;

using namespace std;

ll RES[1000001] = {0};

// ll solve(const int & N){
// 	if( N <= 0) return 0;
// 	if (N <= 2) return N;
// 	if( N == 3) return 4;
// 	if(RES[N]) return RES[N];
// 	ll res = ( (solve(N)%MOD) + (solve(N-2)%MOD) + (solve(N-3)%MOD) ) % MOD;
	
// 	RES[N] = res;
// 	return res;
// }

int _index= 4;

ll solve(const int & N){
	if( N <= 0) return 0;
	if (N <= 2) return N;
	if( N == 3) return 4;
	if(RES[N]) return RES[N];
	
	
	while(_index <= N){
		RES[_index] =( (RES[_index-1]%MOD) + (RES[_index-2] % MOD) + (RES[_index-3]%MOD) ) %MOD;
		_index++;
	}
	return RES[N];
}

int main(){
	RES[0] = 0;
	RES[1] = 1;
	RES[2] = 2;
	RES[3] = 4;
	//input
	int N,T;
	cin>>T;
	for(int i = 0 ; i < T; i++){
		cin>>N;
		cout<<solve(N)<<endl;
	}
	cout<<endl;
	return 0;
}