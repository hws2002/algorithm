#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;

vector<int> l;

void solve(){
	cin>>n;
	l.resize(n);
	for(int i = 0; i < n; i++){
		cin>>l[i];
	}
	
	sort(l.begin(), l.end());

	int ret = 0;
	
	for(int i = 1; i < n ; i++){
		ret += i * l[n-i];
	}
	
	ret+= l[0] * (n-1);
	cout<<ret<<endl;
}

int main(){
	int c;
	cin>>c;
	while(c--) solve();
	return 0;
}