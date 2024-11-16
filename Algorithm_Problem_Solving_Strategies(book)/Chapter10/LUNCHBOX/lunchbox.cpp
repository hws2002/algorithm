#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10000
#define endl '\n'
using namespace std;

int N;

vector<pair<int,int>> me;
void solve(){
	cin>>N;
	me.resize(N);
	for(int i = 0 ; i < N; i++){
		cin>>me[i].first;
	}
	
	for(int i = 0 ; i < N; i++){
		cin>>me[i].second;
	}
	
	sort(me.begin(), me.end(), [](const pair<int,int> & p1, const pair<int,int> & p2){
		return p1.second > p2.second;
	});
	
	
	int ret = -1;
	
	int m = 0;
	for(auto & p : me){
		// printf("%d ,%d ", p.first, p.second);
		m += p.first;
		// printf("m : %d \n", m );
		ret = max(ret, p.second + m);
	}
	
	cout<<ret<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}