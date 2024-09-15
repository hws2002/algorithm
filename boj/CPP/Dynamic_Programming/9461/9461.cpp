#include <iostream>
typedef long long ll;

using namespace std;

int N;
ll cache[101] = {0};

ll P(int N){
	if(N < 0) return 0;
	ll& ret = cache[N];
	if(ret) return ret;
	return ret = P(N-5) + P(N-1);
}

void solve(){
	cin>>N;
	cout<<P(N-1)<<endl;
}
int main(){
	int T;
	cin>>T;
	cache[0] = 1;
	cache[1] = 1;
	cache[2] = 1;
	cache[3] = 2;
	cache[4] = 2;
	while(T--){
		solve();
	}
	return 0;
}