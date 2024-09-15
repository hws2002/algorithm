#include <iostream>
#include <map>
#define endl '\n'

using namespace std;

map<string, string> m;
int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	
	int N,M;
	cin>>N>>M;
	string site, pass;
	while(N--){
		cin>>site>>pass;
		m[site] = pass;
	}
	
	while(M--){
		cin>>site;
		cout<<m[site]<<endl;
	}
	return 0;
}