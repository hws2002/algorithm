#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define endl '\n'
using namespace std;

int n;


void solve(){
	cin>>n;
	priority_queue<int> pq;
	int temp;
	for(int i = 0; i < n; i++){
		cin>>temp;
		pq.push(-temp);
	}
	
	int ret = 0;
	while(pq.size() >= 2){
		int smallest1 = -pq.top(); pq.pop();
		int smallest2 = -pq.top(); pq.pop();
		// printf("s1 ,s2 : %d %d \n", smallest1, smallest2);
		ret += smallest1 + smallest2;
		pq.push(-(smallest1 + smallest2));
	}
	
	cout<<ret<<endl;
}

int main(){
	int c;
	cin>>c;
	while(c--) solve();
	return 0;
}