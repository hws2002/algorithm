#include <iostream>
#include <queue>

#define endl '\n'
using namespace std;
int K,N;

struct RNG{
	public:
		unsigned seed;
		RNG() : seed(1983) {};
		int next(){
			unsigned ret = seed;
			seed = ((seed * 214013u) + 2531011u);
			return ret % 10000 + 1;
		}
};

void solve(){
	RNG rng;
	cin>>K>>N;
	int sum = 0; int ret = 0;
	queue<int> q;
	for(int i = 0; i < N; i++){
		int nxt = rng.next();
		q.push(nxt);
		sum+=nxt;
		while( sum > K){
			sum -= q.front(); q.pop();
		}
		
		ret += sum == K;
	}
	cout<<ret<<endl;
}

int main(){
	int c; cin>>c; while(c--) solve();
	return 0;
}